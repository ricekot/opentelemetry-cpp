// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#ifdef ENABLE_LOGS_PREVIEW

#  include <gtest/gtest.h>

#  include "opentelemetry/exporters/otlp/otlp_http_log_exporter_factory.h"
#  include "opentelemetry/exporters/otlp/otlp_http_log_exporter_options.h"

/*
  Make sure OtlpHttpExporterFactory does not require,
  even indirectly, nlohmann/json headers.
*/
#  ifdef NLOHMANN_JSON_VERSION_MAJOR
#    error "nlohmann/json should not be included"
#  endif /* NLOHMANN_JSON_VERSION_MAJOR */

/*
  Make sure OtlpHttpExporterFactory does not require,
  even indirectly, protobuf headers.
*/
#  ifdef GOOGLE_PROTOBUF_VERSION
#    error "protobuf should not be included"
#  endif

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

TEST(OtlpHttpLogExporterFactoryTest, BuildTest)
{
  OtlpHttpLogExporterOptions opts;
  opts.url = "localhost:45454";

  std::unique_ptr<opentelemetry::sdk::logs::LogExporter> exporter =
      OtlpHttpLogExporterFactory::Create(opts);

  EXPECT_TRUE(exporter != nullptr);
}

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE

#endif  // ENABLE_LOGS_PREVIEW
