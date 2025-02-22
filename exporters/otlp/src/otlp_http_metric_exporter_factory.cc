// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef ENABLE_METRICS_PREVIEW

#  include "opentelemetry/exporters/otlp/otlp_http_metric_exporter_factory.h"
#  include "opentelemetry/exporters/otlp/otlp_http_metric_exporter.h"
#  include "opentelemetry/exporters/otlp/otlp_http_metric_exporter_options.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> OtlpHttpMetricExporterFactory::Create()
{
  OtlpHttpMetricExporterOptions options;
  return Create(options);
}

std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> OtlpHttpMetricExporterFactory::Create(
    const OtlpHttpMetricExporterOptions &options)
{
  std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> exporter(
      new OtlpHttpMetricExporter(options));
  return exporter;
}

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE

#endif
