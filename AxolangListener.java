// Generated from Axolang.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link AxolangParser}.
 */
public interface AxolangListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link AxolangParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(AxolangParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(AxolangParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(AxolangParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(AxolangParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#varDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVarDeclaration(AxolangParser.VarDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#varDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVarDeclaration(AxolangParser.VarDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(AxolangParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(AxolangParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#matchStatement}.
	 * @param ctx the parse tree
	 */
	void enterMatchStatement(AxolangParser.MatchStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#matchStatement}.
	 * @param ctx the parse tree
	 */
	void exitMatchStatement(AxolangParser.MatchStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#matchCase}.
	 * @param ctx the parse tree
	 */
	void enterMatchCase(AxolangParser.MatchCaseContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#matchCase}.
	 * @param ctx the parse tree
	 */
	void exitMatchCase(AxolangParser.MatchCaseContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(AxolangParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(AxolangParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#pkg}.
	 * @param ctx the parse tree
	 */
	void enterPkg(AxolangParser.PkgContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#pkg}.
	 * @param ctx the parse tree
	 */
	void exitPkg(AxolangParser.PkgContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(AxolangParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(AxolangParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void enterArrayLiteral(AxolangParser.ArrayLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void exitArrayLiteral(AxolangParser.ArrayLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link AxolangParser#arrayAccess}.
	 * @param ctx the parse tree
	 */
	void enterArrayAccess(AxolangParser.ArrayAccessContext ctx);
	/**
	 * Exit a parse tree produced by {@link AxolangParser#arrayAccess}.
	 * @param ctx the parse tree
	 */
	void exitArrayAccess(AxolangParser.ArrayAccessContext ctx);
}