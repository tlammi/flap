# Flap grammar
```
file : root_entry*

root_entry:
	module_entry |
	namespace_oneline |
	namespace_scope |
	func_dec |
	func_def |
	func_pattern |
	variable_dec |
	variable_def

module_entry: "module" nsmod_path
namespace_oneline: "namespace" nsmod_path
namespace_scope: "namespace" nsmod_path "{" root_entry* "}"

func_def: identifier ":" func_proto ":=" func_body
func_proto: "(" param* ")" "->" type
func_body: expr | "{" statement* "}"
func_pattern: identifier "(" arg* ")" where_stmt? "=>" expr_or_statements
where_stmt: "where" expr
expr_or_statements: expr | statement*

expr: identifier | int_literal | float_literal | binop | prefix_op | suffix_op
binop: expr operator expr
prefix_op: operator expr
suffix_op: expr operator
statement: return_statement | variable_dec | variable_def

return_statement: "return" expr
variable_dec: identifier ":" type
variable_def: identifier (":" type)? ":=" expr
```

