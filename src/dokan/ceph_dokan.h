/*
 * Copyright (C) 2021 SUSE LINUX GmbH
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
*/

#pragma once

#define CEPH_DOKAN_IO_DEFAULT_TIMEOUT 60 * 5 // Seconds
#define CEPH_DOKAN_DEFAULT_THREAD_COUNT 10

typedef DWORD NTSTATUS;
// Avoid conflicting COM types, exposed when using C++.
#define _OLE2_H_

#include <dokan.h>

struct Config {
  bool removable = false;
  bool readonly = false;
  bool use_win_mount_mgr = false;
  bool current_session_only = false;
  bool debug = false;
  bool dokan_stderr = false;

  int operation_timeout = CEPH_DOKAN_IO_DEFAULT_TIMEOUT;
  int thread_count = CEPH_DOKAN_DEFAULT_THREAD_COUNT;

  std::wstring mountpoint = L"";
  std::string root_path = "";
};

extern Config *g_cfg;

// TODO: list and unmap commands.
enum class Command {
  None,
  Version,
  Help,
  Map,
};

void print_usage();
int parse_args(
  std::vector<const char*>& args,
  std::ostream *err_msg,
  Command *command, Config *cfg);
int set_dokan_options(Config *cfg, PDOKAN_OPTIONS dokan_options);
