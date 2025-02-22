// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#ifndef ENABLE_METRICS_PREVIEW

#  include "opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_options.h"
#  include "opentelemetry/sdk/metrics/metric_exporter.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

/**
 * Factory class for OtlpGrpcMetricExporter.
 */
class OtlpGrpcMetricExporterFactory
{
public:
  /**
   * Create a OtlpGrpcMetricExporter.
   */
  static std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> Create();

  /**
   * Create a OtlpGrpcMetricExporter.
   */
  static std::unique_ptr<opentelemetry::sdk::metrics::MetricExporter> Create(
      const OtlpGrpcMetricExporterOptions &options);
};

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE

#endif /* ENABLE_METRICS_PREVIEW */
