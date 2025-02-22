// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef ENABLE_METRICS_PREVIEW

#  include "opentelemetry/exporters/otlp/otlp_http_metric_exporter_options.h"
#  include "opentelemetry/sdk/metrics/metric_exporter.h"

#  include <memory>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

/**
 * Factory class for OtlpHttpMetricExporter.
 */
class OtlpHttpMetricExporterFactory
{
public:
  /**
   * Create a OtlpHttpMetricExporter.
   */
  static std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> Create();

  /**
   * Create a OtlpHttpMetricExporter.
   */
  static std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> Create(
      const OtlpHttpMetricExporterOptions &options);
};

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
#endif
