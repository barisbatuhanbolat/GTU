#|
	Author: Barış Batuhan Bolat
	210104004029
	COMPILATION WITHOUT MAKEFILE
	clisp gpp_lexer.lisp
|#

;Token Definitions
(defconstant KW_AND  "and")
(defconstant KW_OR  "or")
(defconstant KW_NOT  "not")
(defconstant KW_EQUAL  "equal")
(defconstant KW_LESS  "less")
(defconstant KW_NIL  "nil")
(defconstant KW_LIST  "list")
(defconstant KW_APPEND  "append")
(defconstant KW_CONCAT  "concat")
(defconstant KW_SET  "set")
(defconstant KW_DEF  "def")
(defconstant KW_FOR  "for")
(defconstant KW_IF  "if")
(defconstant KW_EXIT  "exit")
(defconstant KW_LOAD  "load")
(defconstant KW_DISPLAY  "display")
(defconstant KW_TRUE  "true")
(defconstant KW_FALSE  "false")
(defconstant OP_PLUS  "+")
(defconstant OP_MINUS  "-")
(defconstant OP_DIV  "/")
(defconstant OP_MULT  "*")
(defconstant OP_OP  "(")
(defconstant OP_CP  ")")
(defconstant OP_COMMA  ",")
(defconstant COMMENT  ";")

;Variable initializations

;Identifiers for tokens.
(defvar isOp 0) 
(defvar isIdent 0)
(defvar isValue 0)
(defvar isValueF 0)
(defvar isComment 0)

; Token list as vector(dynamic array)
(defvar tokens (make-array 0 :adjustable t :fill-pointer 0 :element-type 'string)) 

;Temporary variables
(defvar temp "")
(defvar op "")
(defvar i 0)
(defvar j 1)

;Main function
(defun gppinterpreter ()
	;Infinite loop with menu for terminal input or file input
	(loop
		(format t "Main Menu~%")
		(format t "1. Read from terminal~%")
		(format t "2. Read from file~%")
		(format t "3. Exit~%")
		(format t "Enter your choice: ")
		(let ((choice (read)))
			(case choice
				(1 
					(format t "Enter input: ")
					(force-output)
					(let ((input (read-line)))
						(loop :for currChar :across input :do
							(detectToken currChar))
							(detectToken #\Newline)
					)		
				)
				(2
					(with-open-file (stream "input.txt")
						(loop :for currChar := (read-char stream nil) :while currChar :collect 
							(detectToken currChar) 
						)
					)
				)
				(3 (return))
			)
		(loop :for i :from 0 :below (or (length tokens) (1+ (length tokens))) :do
			(if (and (string= (aref tokens i) "COMMENT") (string= (aref tokens (1+ i)) "COMMENT"))
			(progn
				(format t "COMMENT~%")
				(incf i))
			(format t "~A~%" (aref tokens i))))
		)

		(setf (fill-pointer tokens) 0)
		(adjust-array tokens 0 :fill-pointer 0)
	)
)
;Detects tokens type and sends it to the addToken function. If token is not valid it adds "SYNTAX_ERROR" word to the list.
(defun detectToken (currChar)
	(cond
		((string-equal currChar COMMENT)
			(setf isComment 1 )
			(addToken currChar))
		((char= currChar #\Newline)
			(setf isComment 0)
			(addToken temp))
		((and (eq isComment 0))
			(cond
				((and (or (char= currChar #\Space ) (char= currChar #\Tab)))
					(addToken temp))		
				((and (eq isComment 0) (> (length temp) 0)(not(eq (isOp currChar) -1))) 
					(addToken temp)
					(setf op (concatenate 'string op (list currChar)))
					(setf isOp (isOp currChar))
					(setf isIdent 0)
					(addToken op)
					(setf op "")
					(setf isOp -1))
				((and (not(eq (isOp currChar) -1)))
					(setf op (concatenate 'string op (list currChar)))
					(setf isOp (isOp currChar))
					(setf isIdent 0)
					(addToken op)
					(setf op "")
					(setf isOp -1))		
				((and (alpha-char-p currChar))
					(setf temp (concatenate 'string temp (list currChar)))
					(setf isIdent 1))
				((and (find currChar "0123456789"))
					(setf temp (concatenate 'string temp (list currChar)))
					(setf isIdent 1)
					(setf isValue 1))
				(t
					(vector-push-extend "SYNTAX ERROR" tokens))
			)
		)
	)
)
; Detects operators type
(defun isOp (var)
	(cond
		( (string-equal var OP_OP)1)
		( (string-equal var OP_CP)2)
		( (string-equal var OP_PLUS)3)
		( (string-equal var OP_MINUS)4)
		( (string-equal var OP_MULT)5)
		( (string-equal var OP_DIV)6)
		( (string-equal var OP_COMMA)7)
		(t -1)
	)
)
; Adds proper word for type of token
(defun addToken (token)
	(cond
		((eq isOp 1) 
			(vector-push-extend "OP_OP" tokens)
		)
		((eq isOp 2) 
			(vector-push-extend "OP_CP" tokens)
		)
		((eq isOp 3) 
			(vector-push-extend "OP_PLUS" tokens)
		)
		((eq isOp 4) 
			(vector-push-extend "OP_MINUS" tokens)
		)
		((eq isOp 5) 
			(vector-push-extend "OP_MULT" tokens)
		)
		((eq isOp 6) 
			(vector-push-extend "OP_DIV" tokens)
		)
		((eq isOp 7) 
			(vector-push-extend "OP_COMMA" tokens)
		)

		((string-equal token COMMENT)
			(vector-push-extend "COMMENT" tokens))

		((string-equal token KW_TRUE)
            (vector-push-extend "KW_TRUE" tokens)
			(setf temp ""))

		((string-equal token KW_FALSE)
            (vector-push-extend "KW_FALSE" tokens)
			(setf temp ""))

		((string-equal token KW_AND)
            (vector-push-extend "KW_AND" tokens)
			(setf temp ""))

	 	((string-equal token KW_OR)
            (vector-push-extend "KW_OR" tokens)
			(setf temp ""))
	 	
	 	((string-equal token KW_NOT)
            (vector-push-extend "KW_NOT" tokens)
			(setf temp ""))

	 	((string-equal token KW_EQUAL)
            (vector-push-extend "KW_EQUAL" tokens)
			(setf temp ""))

	 	((string-equal token KW_APPEND)
            (vector-push-extend "KW_APPEND" tokens)
			(setf temp ""))

	 	((string-equal token KW_NIL)
            (vector-push-extend "KW_NIL" tokens)
			(setf temp ""))

	 	((string-equal token KW_LIST)
            (vector-push-extend "KW_LIST" tokens)
			(setf temp ""))

	 	((string-equal token KW_LESS)
            (vector-push-extend "KW_LESS" tokens)
			(setf temp ""))

	 	((string-equal token KW_CONCAT)
            (vector-push-extend "KW_CONCAT" tokens)
			(setf temp ""))

	 	((string-equal token KW_SET)
            (vector-push-extend "KW_SET" tokens)
			(setf temp ""))

	 	((string-equal token KW_DEF)
            (vector-push-extend "KW_DEF" tokens)
			(setf temp ""))

	 	((string-equal token KW_FOR)
            (vector-push-extend "KW_FOR" tokens)
			(setf temp ""))

	 	((string-equal token KW_IF)
            (vector-push-extend "KW_IF" tokens)
			(setf temp ""))

	 	((string-equal token KW_LOAD)
            (vector-push-extend "KW_LOAD" tokens)
			(setf temp ""))

	 	((string-equal token KW_DISPLAY)
            (vector-push-extend "KW_DISPLAY" tokens)
			(setf temp ""))

	 	((string-equal token KW_EXIT)
            (vector-push-extend "KW_EXIT" tokens)
			(setf temp ""))

	 	((and (eq isValue 0)(eq isIdent 1))
            (vector-push-extend "IDENTIFIER" tokens)
	 		(setf temp "")
	 		(setf isIdent 0))

		((and (eq isValue 1) (> (length temp) 0) (digit-char-p (char temp 0)))
			(loop for char across temp
					when (char= char #\b)
					do (setf isValueF 1))
			(cond
				((not(some #'alpha-char-p temp))
					(vector-push-extend "VALUE" tokens)
					(setf temp "")
					(setf isValue 0)
				)
				((eq isValueF 1)
					(vector-push-extend "VALUEF" tokens)
					(setf temp "")
					(setf isValue 0)				
				)
				((eq isValueF 0)
					(vector-push-extend "SYNTAX_ERROR_DIGIT_START" tokens)
					(setf temp "")
					(setf isValue 0)
				)			
			)
		)		
	)
)

; Calling main function
(gppinterpreter)
