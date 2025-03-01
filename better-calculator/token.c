// Big thanks to https://fenga.medium.com/how-to-build-a-calculator-bf558e6bd8eb

typedef enum {
    INT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    POWER,
    LPAREN,
    RPAREN,
    EOF_TOKEN,
    ILLEGAL
} TokenType;

typedef struct {
    TokenType type;
    char literal[32]; 
} Token;

// AST Node definitions
typedef enum {
    AST_INT,
    AST_OP
} NodeType;

typedef struct ASTNode {
    NodeType type;
    Token token;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

// Constant macro
#define MAX_TOKENS 128

Token tokens[MAX_TOKENS];
int tokenCount = 0;
int currentTokenIndex = 0;

// I have no idea how to procced past this :(