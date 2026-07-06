// Generated from Axolang.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class AxolangParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, IDENTIFIER=24, 
		CHAR_LITERAL=25, STRING_LITERAL=26, INT_LITERAL=27, UINT_LITERAL=28, FLOAT_LITERAL=29, 
		DECIMAL_LITERAL=30, COMPLEX_LITERAL=31, BOOLEAN=32, WS=33, OTHER=34;
	public static final int
		RULE_program = 0, RULE_statement = 1, RULE_varDeclaration = 2, RULE_type = 3, 
		RULE_matchStatement = 4, RULE_matchCase = 5, RULE_declaration = 6, RULE_pkg = 7, 
		RULE_expression = 8, RULE_arrayLiteral = 9, RULE_arrayAccess = 10;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "statement", "varDeclaration", "type", "matchStatement", "matchCase", 
			"declaration", "pkg", "expression", "arrayLiteral", "arrayAccess"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "' '", "'='", "'['", "']'", "'xxsvar'", "'xsvar'", "'svar'", "'var'", 
			"'lvar'", "'xlvar'", "'xxlvar'", "'fun'", "'match'", "'('", "')'", "'{'", 
			"'}'", "'->'", "';'", "'_'", "'\\u00AB'", "','", "'\\u00BB'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			"IDENTIFIER", "CHAR_LITERAL", "STRING_LITERAL", "INT_LITERAL", "UINT_LITERAL", 
			"FLOAT_LITERAL", "DECIMAL_LITERAL", "COMPLEX_LITERAL", "BOOLEAN", "WS", 
			"OTHER"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Axolang.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public AxolangParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(AxolangParser.EOF, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitProgram(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(25);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 16354L) != 0)) {
				{
				{
				setState(22);
				statement();
				}
				}
				setState(27);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(28);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public VarDeclarationContext varDeclaration() {
			return getRuleContext(VarDeclarationContext.class,0);
		}
		public MatchStatementContext matchStatement() {
			return getRuleContext(MatchStatementContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitStatement(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			int _alt;
			setState(44);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(33);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,1,_ctx);
				while ( _alt!=1 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1+1 ) {
						{
						{
						setState(30);
						match(T__0);
						}
						} 
					}
					setState(35);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,1,_ctx);
				}
				setState(36);
				varDeclaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(40);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				while ( _alt!=1 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1+1 ) {
						{
						{
						setState(37);
						match(T__0);
						}
						} 
					}
					setState(42);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				}
				setState(43);
				matchStatement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarDeclarationContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(AxolangParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ArrayLiteralContext arrayLiteral() {
			return getRuleContext(ArrayLiteralContext.class,0);
		}
		public TerminalNode INT_LITERAL() { return getToken(AxolangParser.INT_LITERAL, 0); }
		public VarDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterVarDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitVarDeclaration(this);
		}
	}

	public final VarDeclarationContext varDeclaration() throws RecognitionException {
		VarDeclarationContext _localctx = new VarDeclarationContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_varDeclaration);
		int _la;
		try {
			setState(70);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(46);
				type();
				setState(47);
				match(IDENTIFIER);
				setState(48);
				match(T__1);
				setState(49);
				expression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(51);
				type();
				setState(52);
				match(IDENTIFIER);
				setState(53);
				match(T__2);
				setState(55);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==INT_LITERAL) {
					{
					setState(54);
					match(INT_LITERAL);
					}
				}

				setState(57);
				match(T__3);
				setState(58);
				match(T__1);
				setState(59);
				arrayLiteral();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(61);
				type();
				setState(62);
				match(IDENTIFIER);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(64);
				type();
				setState(65);
				match(IDENTIFIER);
				setState(66);
				match(T__2);
				setState(67);
				match(INT_LITERAL);
				setState(68);
				match(T__3);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypeContext extends ParserRuleContext {
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitType(this);
		}
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(72);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 8160L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MatchStatementContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AxolangParser.IDENTIFIER, 0); }
		public List<MatchCaseContext> matchCase() {
			return getRuleContexts(MatchCaseContext.class);
		}
		public MatchCaseContext matchCase(int i) {
			return getRuleContext(MatchCaseContext.class,i);
		}
		public MatchStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_matchStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterMatchStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitMatchStatement(this);
		}
	}

	public final MatchStatementContext matchStatement() throws RecognitionException {
		MatchStatementContext _localctx = new MatchStatementContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_matchStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(74);
			match(T__12);
			setState(75);
			match(T__13);
			setState(76);
			match(IDENTIFIER);
			setState(77);
			match(T__14);
			setState(78);
			match(T__15);
			setState(80); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(79);
				matchCase();
				}
				}
				setState(82); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 8576368642L) != 0) );
			setState(84);
			match(T__16);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MatchCaseContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public DeclarationContext declaration() {
			return getRuleContext(DeclarationContext.class,0);
		}
		public TerminalNode OTHER() { return getToken(AxolangParser.OTHER, 0); }
		public MatchCaseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_matchCase; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterMatchCase(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitMatchCase(this);
		}
	}

	public final MatchCaseContext matchCase() throws RecognitionException {
		MatchCaseContext _localctx = new MatchCaseContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_matchCase);
		try {
			setState(102);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(86);
				expression();
				setState(87);
				match(T__17);
				setState(88);
				declaration();
				setState(89);
				match(T__18);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(91);
				expression();
				setState(92);
				match(T__17);
				setState(93);
				match(T__15);
				setState(94);
				match(OTHER);
				setState(95);
				match(T__16);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(97);
				match(T__19);
				setState(98);
				match(T__17);
				setState(99);
				declaration();
				setState(100);
				match(T__18);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DeclarationContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AxolangParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode OTHER() { return getToken(AxolangParser.OTHER, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitDeclaration(this);
		}
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_declaration);
		try {
			setState(112);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(104);
				match(IDENTIFIER);
				setState(105);
				match(T__1);
				setState(106);
				expression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(107);
				match(IDENTIFIER);
				setState(108);
				match(T__13);
				setState(109);
				match(OTHER);
				setState(110);
				match(T__14);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(111);
				statement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PkgContext extends ParserRuleContext {
		public List<VarDeclarationContext> varDeclaration() {
			return getRuleContexts(VarDeclarationContext.class);
		}
		public VarDeclarationContext varDeclaration(int i) {
			return getRuleContext(VarDeclarationContext.class,i);
		}
		public PkgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pkg; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterPkg(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitPkg(this);
		}
	}

	public final PkgContext pkg() throws RecognitionException {
		PkgContext _localctx = new PkgContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_pkg);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(117);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,9,_ctx);
			while ( _alt!=1 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1+1 ) {
					{
					{
					setState(114);
					match(T__0);
					}
					} 
				}
				setState(119);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,9,_ctx);
			}
			setState(120);
			match(T__15);
			setState(124);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 8160L) != 0)) {
				{
				{
				setState(121);
				varDeclaration();
				}
				}
				setState(126);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(127);
			match(T__16);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public TerminalNode INT_LITERAL() { return getToken(AxolangParser.INT_LITERAL, 0); }
		public TerminalNode UINT_LITERAL() { return getToken(AxolangParser.UINT_LITERAL, 0); }
		public TerminalNode FLOAT_LITERAL() { return getToken(AxolangParser.FLOAT_LITERAL, 0); }
		public TerminalNode IDENTIFIER() { return getToken(AxolangParser.IDENTIFIER, 0); }
		public TerminalNode COMPLEX_LITERAL() { return getToken(AxolangParser.COMPLEX_LITERAL, 0); }
		public TerminalNode CHAR_LITERAL() { return getToken(AxolangParser.CHAR_LITERAL, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(AxolangParser.STRING_LITERAL, 0); }
		public TerminalNode DECIMAL_LITERAL() { return getToken(AxolangParser.DECIMAL_LITERAL, 0); }
		public PkgContext pkg() {
			return getRuleContext(PkgContext.class,0);
		}
		public TerminalNode BOOLEAN() { return getToken(AxolangParser.BOOLEAN, 0); }
		public ArrayLiteralContext arrayLiteral() {
			return getRuleContext(ArrayLiteralContext.class,0);
		}
		public ArrayAccessContext arrayAccess() {
			return getRuleContext(ArrayAccessContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitExpression(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_expression);
		try {
			setState(141);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(129);
				match(INT_LITERAL);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(130);
				match(UINT_LITERAL);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(131);
				match(FLOAT_LITERAL);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(132);
				match(IDENTIFIER);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(133);
				match(COMPLEX_LITERAL);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(134);
				match(CHAR_LITERAL);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(135);
				match(STRING_LITERAL);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(136);
				match(DECIMAL_LITERAL);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(137);
				pkg();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(138);
				match(BOOLEAN);
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(139);
				arrayLiteral();
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(140);
				arrayAccess();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArrayLiteralContext extends ParserRuleContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ArrayLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayLiteral; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterArrayLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitArrayLiteral(this);
		}
	}

	public final ArrayLiteralContext arrayLiteral() throws RecognitionException {
		ArrayLiteralContext _localctx = new ArrayLiteralContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_arrayLiteral);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(143);
			match(T__20);
			setState(145);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				{
				setState(144);
				match(T__0);
				}
				break;
			}
			setState(147);
			expression();
			setState(155);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__21) {
				{
				{
				setState(148);
				match(T__21);
				setState(150);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
				case 1:
					{
					setState(149);
					match(T__0);
					}
					break;
				}
				setState(152);
				expression();
				}
				}
				setState(157);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(158);
			match(T__22);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArrayAccessContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AxolangParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ArrayAccessContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayAccess; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).enterArrayAccess(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof AxolangListener ) ((AxolangListener)listener).exitArrayAccess(this);
		}
	}

	public final ArrayAccessContext arrayAccess() throws RecognitionException {
		ArrayAccessContext _localctx = new ArrayAccessContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_arrayAccess);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(160);
			match(IDENTIFIER);
			setState(161);
			match(T__2);
			setState(162);
			expression();
			setState(163);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\"\u00a6\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0001\u0000\u0005\u0000\u0018"+
		"\b\u0000\n\u0000\f\u0000\u001b\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001"+
		"\u0005\u0001 \b\u0001\n\u0001\f\u0001#\t\u0001\u0001\u0001\u0001\u0001"+
		"\u0005\u0001\'\b\u0001\n\u0001\f\u0001*\t\u0001\u0001\u0001\u0003\u0001"+
		"-\b\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u00028\b\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0003\u0002G\b\u0002\u0001\u0003\u0001\u0003\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0004\u0004"+
		"Q\b\u0004\u000b\u0004\f\u0004R\u0001\u0004\u0001\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0003\u0005g\b\u0005\u0001\u0006\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0003\u0006q\b\u0006\u0001\u0007\u0005\u0007t\b\u0007\n\u0007\f"+
		"\u0007w\t\u0007\u0001\u0007\u0001\u0007\u0005\u0007{\b\u0007\n\u0007\f"+
		"\u0007~\t\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0003"+
		"\b\u008e\b\b\u0001\t\u0001\t\u0003\t\u0092\b\t\u0001\t\u0001\t\u0001\t"+
		"\u0003\t\u0097\b\t\u0001\t\u0005\t\u009a\b\t\n\t\f\t\u009d\t\t\u0001\t"+
		"\u0001\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0003!(u\u0000"+
		"\u000b\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0000\u0001"+
		"\u0001\u0000\u0005\f\u00b7\u0000\u0019\u0001\u0000\u0000\u0000\u0002,"+
		"\u0001\u0000\u0000\u0000\u0004F\u0001\u0000\u0000\u0000\u0006H\u0001\u0000"+
		"\u0000\u0000\bJ\u0001\u0000\u0000\u0000\nf\u0001\u0000\u0000\u0000\fp"+
		"\u0001\u0000\u0000\u0000\u000eu\u0001\u0000\u0000\u0000\u0010\u008d\u0001"+
		"\u0000\u0000\u0000\u0012\u008f\u0001\u0000\u0000\u0000\u0014\u00a0\u0001"+
		"\u0000\u0000\u0000\u0016\u0018\u0003\u0002\u0001\u0000\u0017\u0016\u0001"+
		"\u0000\u0000\u0000\u0018\u001b\u0001\u0000\u0000\u0000\u0019\u0017\u0001"+
		"\u0000\u0000\u0000\u0019\u001a\u0001\u0000\u0000\u0000\u001a\u001c\u0001"+
		"\u0000\u0000\u0000\u001b\u0019\u0001\u0000\u0000\u0000\u001c\u001d\u0005"+
		"\u0000\u0000\u0001\u001d\u0001\u0001\u0000\u0000\u0000\u001e \u0005\u0001"+
		"\u0000\u0000\u001f\u001e\u0001\u0000\u0000\u0000 #\u0001\u0000\u0000\u0000"+
		"!\"\u0001\u0000\u0000\u0000!\u001f\u0001\u0000\u0000\u0000\"$\u0001\u0000"+
		"\u0000\u0000#!\u0001\u0000\u0000\u0000$-\u0003\u0004\u0002\u0000%\'\u0005"+
		"\u0001\u0000\u0000&%\u0001\u0000\u0000\u0000\'*\u0001\u0000\u0000\u0000"+
		"()\u0001\u0000\u0000\u0000(&\u0001\u0000\u0000\u0000)+\u0001\u0000\u0000"+
		"\u0000*(\u0001\u0000\u0000\u0000+-\u0003\b\u0004\u0000,!\u0001\u0000\u0000"+
		"\u0000,(\u0001\u0000\u0000\u0000-\u0003\u0001\u0000\u0000\u0000./\u0003"+
		"\u0006\u0003\u0000/0\u0005\u0018\u0000\u000001\u0005\u0002\u0000\u0000"+
		"12\u0003\u0010\b\u00002G\u0001\u0000\u0000\u000034\u0003\u0006\u0003\u0000"+
		"45\u0005\u0018\u0000\u000057\u0005\u0003\u0000\u000068\u0005\u001b\u0000"+
		"\u000076\u0001\u0000\u0000\u000078\u0001\u0000\u0000\u000089\u0001\u0000"+
		"\u0000\u00009:\u0005\u0004\u0000\u0000:;\u0005\u0002\u0000\u0000;<\u0003"+
		"\u0012\t\u0000<G\u0001\u0000\u0000\u0000=>\u0003\u0006\u0003\u0000>?\u0005"+
		"\u0018\u0000\u0000?G\u0001\u0000\u0000\u0000@A\u0003\u0006\u0003\u0000"+
		"AB\u0005\u0018\u0000\u0000BC\u0005\u0003\u0000\u0000CD\u0005\u001b\u0000"+
		"\u0000DE\u0005\u0004\u0000\u0000EG\u0001\u0000\u0000\u0000F.\u0001\u0000"+
		"\u0000\u0000F3\u0001\u0000\u0000\u0000F=\u0001\u0000\u0000\u0000F@\u0001"+
		"\u0000\u0000\u0000G\u0005\u0001\u0000\u0000\u0000HI\u0007\u0000\u0000"+
		"\u0000I\u0007\u0001\u0000\u0000\u0000JK\u0005\r\u0000\u0000KL\u0005\u000e"+
		"\u0000\u0000LM\u0005\u0018\u0000\u0000MN\u0005\u000f\u0000\u0000NP\u0005"+
		"\u0010\u0000\u0000OQ\u0003\n\u0005\u0000PO\u0001\u0000\u0000\u0000QR\u0001"+
		"\u0000\u0000\u0000RP\u0001\u0000\u0000\u0000RS\u0001\u0000\u0000\u0000"+
		"ST\u0001\u0000\u0000\u0000TU\u0005\u0011\u0000\u0000U\t\u0001\u0000\u0000"+
		"\u0000VW\u0003\u0010\b\u0000WX\u0005\u0012\u0000\u0000XY\u0003\f\u0006"+
		"\u0000YZ\u0005\u0013\u0000\u0000Zg\u0001\u0000\u0000\u0000[\\\u0003\u0010"+
		"\b\u0000\\]\u0005\u0012\u0000\u0000]^\u0005\u0010\u0000\u0000^_\u0005"+
		"\"\u0000\u0000_`\u0005\u0011\u0000\u0000`g\u0001\u0000\u0000\u0000ab\u0005"+
		"\u0014\u0000\u0000bc\u0005\u0012\u0000\u0000cd\u0003\f\u0006\u0000de\u0005"+
		"\u0013\u0000\u0000eg\u0001\u0000\u0000\u0000fV\u0001\u0000\u0000\u0000"+
		"f[\u0001\u0000\u0000\u0000fa\u0001\u0000\u0000\u0000g\u000b\u0001\u0000"+
		"\u0000\u0000hi\u0005\u0018\u0000\u0000ij\u0005\u0002\u0000\u0000jq\u0003"+
		"\u0010\b\u0000kl\u0005\u0018\u0000\u0000lm\u0005\u000e\u0000\u0000mn\u0005"+
		"\"\u0000\u0000nq\u0005\u000f\u0000\u0000oq\u0003\u0002\u0001\u0000ph\u0001"+
		"\u0000\u0000\u0000pk\u0001\u0000\u0000\u0000po\u0001\u0000\u0000\u0000"+
		"q\r\u0001\u0000\u0000\u0000rt\u0005\u0001\u0000\u0000sr\u0001\u0000\u0000"+
		"\u0000tw\u0001\u0000\u0000\u0000uv\u0001\u0000\u0000\u0000us\u0001\u0000"+
		"\u0000\u0000vx\u0001\u0000\u0000\u0000wu\u0001\u0000\u0000\u0000x|\u0005"+
		"\u0010\u0000\u0000y{\u0003\u0004\u0002\u0000zy\u0001\u0000\u0000\u0000"+
		"{~\u0001\u0000\u0000\u0000|z\u0001\u0000\u0000\u0000|}\u0001\u0000\u0000"+
		"\u0000}\u007f\u0001\u0000\u0000\u0000~|\u0001\u0000\u0000\u0000\u007f"+
		"\u0080\u0005\u0011\u0000\u0000\u0080\u000f\u0001\u0000\u0000\u0000\u0081"+
		"\u008e\u0005\u001b\u0000\u0000\u0082\u008e\u0005\u001c\u0000\u0000\u0083"+
		"\u008e\u0005\u001d\u0000\u0000\u0084\u008e\u0005\u0018\u0000\u0000\u0085"+
		"\u008e\u0005\u001f\u0000\u0000\u0086\u008e\u0005\u0019\u0000\u0000\u0087"+
		"\u008e\u0005\u001a\u0000\u0000\u0088\u008e\u0005\u001e\u0000\u0000\u0089"+
		"\u008e\u0003\u000e\u0007\u0000\u008a\u008e\u0005 \u0000\u0000\u008b\u008e"+
		"\u0003\u0012\t\u0000\u008c\u008e\u0003\u0014\n\u0000\u008d\u0081\u0001"+
		"\u0000\u0000\u0000\u008d\u0082\u0001\u0000\u0000\u0000\u008d\u0083\u0001"+
		"\u0000\u0000\u0000\u008d\u0084\u0001\u0000\u0000\u0000\u008d\u0085\u0001"+
		"\u0000\u0000\u0000\u008d\u0086\u0001\u0000\u0000\u0000\u008d\u0087\u0001"+
		"\u0000\u0000\u0000\u008d\u0088\u0001\u0000\u0000\u0000\u008d\u0089\u0001"+
		"\u0000\u0000\u0000\u008d\u008a\u0001\u0000\u0000\u0000\u008d\u008b\u0001"+
		"\u0000\u0000\u0000\u008d\u008c\u0001\u0000\u0000\u0000\u008e\u0011\u0001"+
		"\u0000\u0000\u0000\u008f\u0091\u0005\u0015\u0000\u0000\u0090\u0092\u0005"+
		"\u0001\u0000\u0000\u0091\u0090\u0001\u0000\u0000\u0000\u0091\u0092\u0001"+
		"\u0000\u0000\u0000\u0092\u0093\u0001\u0000\u0000\u0000\u0093\u009b\u0003"+
		"\u0010\b\u0000\u0094\u0096\u0005\u0016\u0000\u0000\u0095\u0097\u0005\u0001"+
		"\u0000\u0000\u0096\u0095\u0001\u0000\u0000\u0000\u0096\u0097\u0001\u0000"+
		"\u0000\u0000\u0097\u0098\u0001\u0000\u0000\u0000\u0098\u009a\u0003\u0010"+
		"\b\u0000\u0099\u0094\u0001\u0000\u0000\u0000\u009a\u009d\u0001\u0000\u0000"+
		"\u0000\u009b\u0099\u0001\u0000\u0000\u0000\u009b\u009c\u0001\u0000\u0000"+
		"\u0000\u009c\u009e\u0001\u0000\u0000\u0000\u009d\u009b\u0001\u0000\u0000"+
		"\u0000\u009e\u009f\u0005\u0017\u0000\u0000\u009f\u0013\u0001\u0000\u0000"+
		"\u0000\u00a0\u00a1\u0005\u0018\u0000\u0000\u00a1\u00a2\u0005\u0003\u0000"+
		"\u0000\u00a2\u00a3\u0003\u0010\b\u0000\u00a3\u00a4\u0005\u0004\u0000\u0000"+
		"\u00a4\u0015\u0001\u0000\u0000\u0000\u000f\u0019!(,7FRfpu|\u008d\u0091"+
		"\u0096\u009b";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}