/**
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * This file is part of srsLTE.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef SRSENB_ENB_EVENTS_H
#define SRSENB_ENB_EVENTS_H

#include <cstdint>
#include <memory>

namespace srslog {
class log_channel;
}

namespace srsenb {

/// This interface logs different kinds of events to the configured channel. By default, if no log channel is configured
/// logging will be disabled.
class event_logger_interface
{
public:
  virtual ~event_logger_interface() = default;

  /// Logs into the underlying log channel the RRC connected event.
  virtual void log_rrc_connected(unsigned cause) = 0;

  /// Logs into the underlying log channel the RRC disconnected event.
  virtual void log_rrc_disconnect(unsigned reason) = 0;

  /// Logs into the underlying log channel the S1 context create event.
  virtual void log_s1_ctx_create(uint32_t mme_id, uint32_t enb_id, uint16_t rnti) = 0;

  /// Logs into the underlying log channel the S1 context delete event.
  virtual void log_s1_ctx_delete(uint32_t mme_id, uint32_t enb_id, uint16_t rnti) = 0;

  /// Logs into the underlying log channel the when a sector has been started.
  virtual void log_sector_start(uint32_t cc_idx, uint32_t pci, uint32_t cell_id) = 0;

  /// Logs into the underlying log channel the when a sector has been stopped.
  virtual void log_sector_stop(uint32_t cc_idx, uint32_t pci, uint32_t cell_id) = 0;
};

/// Singleton class to provide global access to the event_logger_interface interface.
class event_logger
{
  event_logger() = default;

public:
  /// Returns the instance of the event logger.
  static event_logger_interface& get();

  /// Uses the specified log channel for event logging.
  /// NOTE: This method is not thread safe.
  static void configure(srslog::log_channel& c);

private:
  static std::unique_ptr<event_logger_interface> pimpl;
};

} // namespace srsenb

#endif // SRSENB_ENB_EVENTS_H
