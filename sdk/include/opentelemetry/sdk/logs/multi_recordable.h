// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#ifdef ENABLE_LOGS_PREVIEW

#  include <cstddef>
#  include <memory>
#  include <unordered_map>

#  include "opentelemetry/common/macros.h"
#  include "opentelemetry/sdk/logs/processor.h"
#  include "opentelemetry/sdk/logs/recordable.h"
#  include "opentelemetry/sdk/resource/resource.h"
#  include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace logs
{
class MultiRecordable final : public Recordable
{
public:
  void AddRecordable(const LogProcessor &processor,
                     std::unique_ptr<Recordable> recordable) noexcept;

  const std::unique_ptr<Recordable> &GetRecordable(const LogProcessor &processor) const noexcept;

  std::unique_ptr<Recordable> ReleaseRecordable(const LogProcessor &processor) noexcept;

  /**
   * Set the timestamp for this log.
   * @param timestamp the timestamp to set
   */
  void SetTimestamp(opentelemetry::common::SystemTimestamp timestamp) noexcept override;

  /**
   * Set the severity for this log.
   * @param severity the severity of the event
   */
  void SetSeverity(opentelemetry::logs::Severity severity) noexcept override;

  /**
   * Set body field for this log.
   * @param message the body to set
   */
  void SetBody(nostd::string_view message) noexcept override;

  /**
   * Set Resource of this log
   * @param Resource the resource to set
   */
  void SetResource(const opentelemetry::sdk::resource::Resource &resource) noexcept override;

  /**
   * Set an attribute of a log.
   * @param key the name of the attribute
   * @param value the attribute value
   */
  void SetAttribute(nostd::string_view key,
                    const opentelemetry::common::AttributeValue &value) noexcept override;

  /**
   * Set the trace id for this log.
   * @param trace_id the trace id to set
   */
  void SetTraceId(opentelemetry::trace::TraceId trace_id) noexcept override;

  /**
   * Set the span id for this log.
   * @param span_id the span id to set
   */
  void SetSpanId(opentelemetry::trace::SpanId span_id) noexcept override;

  /**
   * Inject trace_flags for this log.
   * @param trace_flags the trace flags to set
   */
  void SetTraceFlags(opentelemetry::trace::TraceFlags trace_flags) noexcept override;

  /**
   * Set instrumentation_scope for this log.
   * @param instrumentation_scope the instrumentation scope to set
   */
  void SetInstrumentationScope(const opentelemetry::sdk::instrumentationscope::InstrumentationScope
                                   &instrumentation_scope) noexcept override;

  /** Returns the associated instrumentation scope */
  const opentelemetry::sdk::instrumentationscope::InstrumentationScope &GetInstrumentationScope()
      const noexcept;

  OPENTELEMETRY_DEPRECATED_MESSAGE("Please use GetInstrumentationScope instead")
  const opentelemetry::sdk::instrumentationscope::InstrumentationScope &GetInstrumentationLibrary()
      const noexcept
  {
    return GetInstrumentationScope();
  }

private:
  std::unordered_map<std::size_t, std::unique_ptr<Recordable>> recordables_;
  const opentelemetry::sdk::instrumentationscope::InstrumentationScope *instrumentation_scope_ =
      nullptr;
};
}  // namespace logs
}  // namespace sdk

OPENTELEMETRY_END_NAMESPACE

#endif
