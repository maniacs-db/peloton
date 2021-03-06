//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// convert_query_to_op.cpp
//
// Identification: src/include/optimizer/query_property_extractor.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "optimizer/column_manager.h"
#include "optimizer/property_set.h"
#include "optimizer/query_node_visitor.h"

namespace peloton {

namespace parser {
class SQLStatement;
}

namespace optimizer {

/*
 * Extract physical properties from the parsed query.
 * Physical properties are those fields that can be directly added to the plan,
 * and don't need to perform transformations on.
 */
class QueryPropertyExtractor : public QueryNodeVisitor {
 public:
  QueryPropertyExtractor(ColumnManager &manager) : manager_(manager) {}

  PropertySet GetProperties(parser::SQLStatement *tree);

  // We only assume the statement is selecting from one table for now
  void Visit(const parser::SelectStatement *) override;

  void Visit(const parser::GroupByDescription *) override;
  void Visit(const parser::OrderDescription *) override;
  void Visit(const parser::LimitDescription *) override;

  void Visit(const parser::CreateStatement *) override;
  void Visit(const parser::InsertStatement *) override;
  void Visit(const parser::DeleteStatement *) override;
  void Visit(const parser::DropStatement *) override;
  void Visit(const parser::PrepareStatement *) override;
  void Visit(const parser::ExecuteStatement *) override;
  void Visit(const parser::TransactionStatement *) override;
  void Visit(const parser::UpdateStatement *) override;
  void Visit(const parser::CopyStatement *) override;

 private:
  ColumnManager &manager_;

  // Required properties by the visitor
  PropertySet property_set_;
};

} /* namespace optimizer */
} /* namespace peloton */
