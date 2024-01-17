#pragma once

#include <optional>
#include <vector>

#include "binlog.pb.h"

namespace storage {

using Slice = rocksdb::Slice;

//或者直接用originalBinlog类，BaikalDB就是没有包装
class Binlog {
 public:
  explicit Binlog(DataType type) {
    originalBinlog.set_type(type);
  }

  void AppendPutOperation(int8_t cfid, const Slice& key, const Slice& value) {
    auto entry = originalBinlog.add_entries();
    entry->set_cfid(cfid);
    entry->set_key(key.ToString());
    entry->set_value(value.ToString());
    entry->set_type(OperateType::kPut);
  }
  void AppendDeleteOperation(int8_t cfid, const Slice& key) {
    auto entry = originalBinlog.add_entries();
    entry->set_cfid(cfid);
    entry->set_key(key.ToString());
    entry->set_type(OperateType::kDelete);
  }

  DataType get_type() {
    return originalBinlog.type();
  }

  auto get_entries_() {
    return originalBinlog.entries();
  }

  OriginalBinlog originalBinlog;

};

}  // namespace storage
