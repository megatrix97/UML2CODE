document
    : START info END
    ;

info
    : 
    | info relationship_info
    | info class_info
    | info classdecl
    ;

relationship_info
    : ID relation ID COLON label
    | relationship_info ID relation ID COLON label
    ;

classdecl
    : CLASS ID LCURLY properties RCURLY NEWLINE
    ;

properties
    : property 
    | properties property
    ;

property
    : ID ID NEWLINE
    | ID ID LPAREN args RPAREN NEWLINE
    ;

access_type
    : PRIVATE
    | PROTECTED
    | PUBLIC
    ;

class_info
    : ID COLON field
    | ID COLON method
    ;

field
    : arg
    | ID LSQUARE RSQUARE ID
    ;

method
    : ID LPAREN args RPAREN
    ;

args
    : arg
    | args COMMA arg
    ;

arg
    : ID ID
    ;

relation
    : ASSOCIATION
    | INHERITANCE
    | COMPOSITION
    | IMPLEMENTION
    | AGGREGATION
    | DEPENDENCY
    ;

label
    : MESSAGE LEFT_ARROW
    | MESSAGE RIGHT_ARROW
    | MESSAGE
    ;