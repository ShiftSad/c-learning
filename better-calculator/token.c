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

