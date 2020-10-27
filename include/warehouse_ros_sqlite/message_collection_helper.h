// SPDX-License-Identifier: BSD-3-Clause

/*
 * Copyright (c) 2020, Bjarne von Horn
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BJARNE VON HORN BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include <warehouse_ros/message_collection.h>
#include <warehouse_ros_sqlite/utils.h>

namespace warehouse_ros_sqlite
{
class MessageCollectionHelper : public warehouse_ros::MessageCollectionHelper
{
  sqlite3_ptr db_;
  std::string name_;
public:
  MessageCollectionHelper() = default;
  MessageCollectionHelper(sqlite3_ptr db, const std::string& name) : db_(std::move(db)), name_(name) {}
  bool initialize(const std::string& datatype, const std::string& md5) override;
  void insert(char* msg, size_t msg_size, warehouse_ros::Metadata::ConstPtr metadata) override;
  warehouse_ros::ResultIteratorHelper::Ptr query(warehouse_ros::Query::ConstPtr query, const std::string& sort_by = "",
                                  bool ascending = true) const override;
  unsigned removeMessages(warehouse_ros::Query::ConstPtr query) override;
  void modifyMetadata(warehouse_ros::Query::ConstPtr q, warehouse_ros::Metadata::ConstPtr m) override;
  unsigned count() override;
  warehouse_ros::Query::Ptr createQuery() const override;
  warehouse_ros::Metadata::Ptr createMetadata() const override;
  std::string collectionName() const override { return name_; }
private:
  std::string find_md5sum();
};

}  // namespace warehouse_ros_sqlite
