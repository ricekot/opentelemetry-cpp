// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef ENABLE_METRICS_PREVIEW
#  include "opentelemetry/sdk/metrics/aggregation/histogram_aggregation.h"
#  include <algorithm>
#  include <iomanip>
#  include <limits>
#  include "opentelemetry/version.h"

#  include <mutex>
OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

LongHistogramAggregation::LongHistogramAggregation(
    const HistogramAggregationConfig<long> *aggregation_config)
{
  if (aggregation_config && aggregation_config->boundaries_.size())
  {
    point_data_.boundaries_ = aggregation_config->boundaries_;
  }
  else
  {
    point_data_.boundaries_ = std::list<long>{0l, 5l, 10l, 25l, 50l, 75l, 100l, 250l, 500l, 1000l};
  }
  if (aggregation_config)
  {
    record_min_max_ = aggregation_config->record_min_max_;
  }
  point_data_.counts_ =
      std::vector<uint64_t>(nostd::get<std::list<long>>(point_data_.boundaries_).size() + 1, 0);
  point_data_.sum_            = 0l;
  point_data_.count_          = 0;
  point_data_.record_min_max_ = record_min_max_;
  point_data_.min_            = std::numeric_limits<long>::max();
  point_data_.max_            = std::numeric_limits<long>::min();
}

LongHistogramAggregation::LongHistogramAggregation(HistogramPointData &&data)
    : point_data_{std::move(data)}, record_min_max_{point_data_.record_min_max_}
{}

LongHistogramAggregation::LongHistogramAggregation(const HistogramPointData &data)
    : point_data_{data}, record_min_max_{point_data_.record_min_max_}
{}

void LongHistogramAggregation::Aggregate(long value,
                                         const PointAttributes & /* attributes */) noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  point_data_.count_ += 1;
  point_data_.sum_ = nostd::get<long>(point_data_.sum_) + value;
  if (record_min_max_)
  {
    point_data_.min_ = std::min(nostd::get<long>(point_data_.min_), value);
    point_data_.max_ = std::max(nostd::get<long>(point_data_.max_), value);
  }
  size_t index = 0;
  for (auto it = nostd::get<std::list<long>>(point_data_.boundaries_).begin();
       it != nostd::get<std::list<long>>(point_data_.boundaries_).end(); ++it)
  {
    if (value < *it)
    {
      point_data_.counts_[index] += 1;
      return;
    }
    index++;
  }
}

std::unique_ptr<Aggregation> LongHistogramAggregation::Merge(
    const Aggregation &delta) const noexcept
{
  auto curr_value  = nostd::get<HistogramPointData>(ToPoint());
  auto delta_value = nostd::get<HistogramPointData>(
      (static_cast<const LongHistogramAggregation &>(delta).ToPoint()));
  LongHistogramAggregation *aggr = new LongHistogramAggregation();
  HistogramMerge<long>(curr_value, delta_value, aggr->point_data_);
  return std::unique_ptr<Aggregation>(aggr);
}

std::unique_ptr<Aggregation> LongHistogramAggregation::Diff(const Aggregation &next) const noexcept
{
  auto curr_value = nostd::get<HistogramPointData>(ToPoint());
  auto next_value = nostd::get<HistogramPointData>(
      (static_cast<const LongHistogramAggregation &>(next).ToPoint()));
  LongHistogramAggregation *aggr = new LongHistogramAggregation();
  HistogramDiff<long>(curr_value, next_value, aggr->point_data_);
  return std::unique_ptr<Aggregation>(aggr);
}

PointType LongHistogramAggregation::ToPoint() const noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  return point_data_;
}

DoubleHistogramAggregation::DoubleHistogramAggregation(
    const HistogramAggregationConfig<double> *aggregation_config)
{
  if (aggregation_config && aggregation_config->boundaries_.size())
  {
    point_data_.boundaries_ = aggregation_config->boundaries_;
  }
  else
  {
    point_data_.boundaries_ =
        std::list<double>{0.0, 5.0, 10.0, 25.0, 50.0, 75.0, 100.0, 250.0, 500.0, 1000.0};
  }
  if (aggregation_config)
  {
    record_min_max_ = aggregation_config->record_min_max_;
  }
  point_data_.counts_ =
      std::vector<uint64_t>(nostd::get<std::list<double>>(point_data_.boundaries_).size() + 1, 0);
  point_data_.sum_            = 0.0;
  point_data_.count_          = 0;
  point_data_.record_min_max_ = record_min_max_;
  point_data_.min_            = std::numeric_limits<double>::max();
  point_data_.max_            = std::numeric_limits<double>::min();
}

DoubleHistogramAggregation::DoubleHistogramAggregation(HistogramPointData &&data)
    : point_data_{std::move(data)}
{}

DoubleHistogramAggregation::DoubleHistogramAggregation(const HistogramPointData &data)
    : point_data_{data}
{}

void DoubleHistogramAggregation::Aggregate(double value,
                                           const PointAttributes & /* attributes */) noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  point_data_.count_ += 1;
  point_data_.sum_ = nostd::get<double>(point_data_.sum_) + value;
  if (record_min_max_)
  {
    point_data_.min_ = std::min(nostd::get<double>(point_data_.min_), value);
    point_data_.max_ = std::max(nostd::get<double>(point_data_.max_), value);
  }
  size_t index = 0;
  for (auto it = nostd::get<std::list<double>>(point_data_.boundaries_).begin();
       it != nostd::get<std::list<double>>(point_data_.boundaries_).end(); ++it)
  {
    if (value < *it)
    {
      point_data_.counts_[index] += 1;
      return;
    }
    index++;
  }
}

std::unique_ptr<Aggregation> DoubleHistogramAggregation::Merge(
    const Aggregation &delta) const noexcept
{
  auto curr_value  = nostd::get<HistogramPointData>(ToPoint());
  auto delta_value = nostd::get<HistogramPointData>(
      (static_cast<const DoubleHistogramAggregation &>(delta).ToPoint()));
  DoubleHistogramAggregation *aggr = new DoubleHistogramAggregation();
  HistogramMerge<double>(curr_value, delta_value, aggr->point_data_);
  return std::unique_ptr<Aggregation>(aggr);
}

std::unique_ptr<Aggregation> DoubleHistogramAggregation::Diff(
    const Aggregation &next) const noexcept
{
  auto curr_value = nostd::get<HistogramPointData>(ToPoint());
  auto next_value = nostd::get<HistogramPointData>(
      (static_cast<const DoubleHistogramAggregation &>(next).ToPoint()));
  DoubleHistogramAggregation *aggr = new DoubleHistogramAggregation();
  HistogramDiff<double>(curr_value, next_value, aggr->point_data_);
  return std::unique_ptr<Aggregation>(aggr);
}

PointType DoubleHistogramAggregation::ToPoint() const noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  return point_data_;
}

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
#endif
