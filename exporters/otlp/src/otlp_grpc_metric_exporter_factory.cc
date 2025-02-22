// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef ENABLE_METRICS_PREVIEW

// MUST be first (absl)
#  include "opentelemetry/exporters/otlp/otlp_grpc_metric_exporter.h"

#  include "opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_factory.h"
#  include "opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_options.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> OtlpGrpcMetricExporterFactory::Create()
{
  OtlpGrpcMetricExporterOptions options;
  return Create(options);
}

std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> OtlpGrpcMetricExporterFactory::Create(
    const OtlpGrpcMetricExporterOptions &options)
{
  std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> exporter(
      new OtlpGrpcMetricExporter(options));
  return exporter;
}

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE

#endif
