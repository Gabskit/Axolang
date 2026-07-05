// Generated from Axolang.g4 by ANTLR 4.13.1
// jshint ignore: start
import antlr4 from 'antlr4';
import AxolangListener from './AxolangListener.js';
const serializedATN = [4,1,34,164,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,5,0,24,8,0,10,0,
12,0,27,9,0,1,0,5,0,30,8,0,10,0,12,0,33,9,0,1,0,1,0,1,1,1,1,3,1,39,8,1,1,
2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,52,8,2,1,2,1,2,1,2,1,2,1,2,
1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,69,8,2,1,3,1,3,1,4,1,4,1,4,1,
4,1,4,1,4,4,4,79,8,4,11,4,12,4,80,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,101,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,
6,1,6,3,6,111,8,6,1,7,5,7,114,8,7,10,7,12,7,117,9,7,1,7,1,7,5,7,121,8,7,
10,7,12,7,124,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
8,3,8,140,8,8,1,9,1,9,3,9,144,8,9,1,9,1,9,1,9,3,9,149,8,9,1,9,5,9,152,8,
9,10,9,12,9,155,9,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,2,25,115,0,11,
0,2,4,6,8,10,12,14,16,18,20,0,1,1,0,5,12,180,0,25,1,0,0,0,2,38,1,0,0,0,4,
68,1,0,0,0,6,70,1,0,0,0,8,72,1,0,0,0,10,100,1,0,0,0,12,110,1,0,0,0,14,115,
1,0,0,0,16,139,1,0,0,0,18,141,1,0,0,0,20,158,1,0,0,0,22,24,5,1,0,0,23,22,
1,0,0,0,24,27,1,0,0,0,25,26,1,0,0,0,25,23,1,0,0,0,26,31,1,0,0,0,27,25,1,
0,0,0,28,30,3,2,1,0,29,28,1,0,0,0,30,33,1,0,0,0,31,29,1,0,0,0,31,32,1,0,
0,0,32,34,1,0,0,0,33,31,1,0,0,0,34,35,5,0,0,1,35,1,1,0,0,0,36,39,3,4,2,0,
37,39,3,8,4,0,38,36,1,0,0,0,38,37,1,0,0,0,39,3,1,0,0,0,40,41,3,6,3,0,41,
42,5,1,0,0,42,43,5,24,0,0,43,44,5,2,0,0,44,45,3,16,8,0,45,69,1,0,0,0,46,
47,3,6,3,0,47,48,5,1,0,0,48,49,5,24,0,0,49,51,5,3,0,0,50,52,5,27,0,0,51,
50,1,0,0,0,51,52,1,0,0,0,52,53,1,0,0,0,53,54,5,4,0,0,54,55,5,2,0,0,55,56,
3,18,9,0,56,69,1,0,0,0,57,58,3,6,3,0,58,59,5,1,0,0,59,60,5,24,0,0,60,69,
1,0,0,0,61,62,3,6,3,0,62,63,5,1,0,0,63,64,5,24,0,0,64,65,5,3,0,0,65,66,5,
27,0,0,66,67,5,4,0,0,67,69,1,0,0,0,68,40,1,0,0,0,68,46,1,0,0,0,68,57,1,0,
0,0,68,61,1,0,0,0,69,5,1,0,0,0,70,71,7,0,0,0,71,7,1,0,0,0,72,73,5,13,0,0,
73,74,5,14,0,0,74,75,5,24,0,0,75,76,5,15,0,0,76,78,5,16,0,0,77,79,3,10,5,
0,78,77,1,0,0,0,79,80,1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,82,1,0,0,0,
82,83,5,17,0,0,83,9,1,0,0,0,84,85,3,16,8,0,85,86,5,18,0,0,86,87,3,12,6,0,
87,88,5,19,0,0,88,101,1,0,0,0,89,90,3,16,8,0,90,91,5,18,0,0,91,92,5,16,0,
0,92,93,5,34,0,0,93,94,5,17,0,0,94,101,1,0,0,0,95,96,5,20,0,0,96,97,5,18,
0,0,97,98,3,12,6,0,98,99,5,19,0,0,99,101,1,0,0,0,100,84,1,0,0,0,100,89,1,
0,0,0,100,95,1,0,0,0,101,11,1,0,0,0,102,103,5,24,0,0,103,104,5,2,0,0,104,
111,3,16,8,0,105,106,5,24,0,0,106,107,5,14,0,0,107,108,5,34,0,0,108,111,
5,15,0,0,109,111,3,2,1,0,110,102,1,0,0,0,110,105,1,0,0,0,110,109,1,0,0,0,
111,13,1,0,0,0,112,114,5,1,0,0,113,112,1,0,0,0,114,117,1,0,0,0,115,116,1,
0,0,0,115,113,1,0,0,0,116,118,1,0,0,0,117,115,1,0,0,0,118,122,5,16,0,0,119,
121,3,4,2,0,120,119,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,123,1,0,
0,0,123,125,1,0,0,0,124,122,1,0,0,0,125,126,5,17,0,0,126,15,1,0,0,0,127,
140,5,27,0,0,128,140,5,28,0,0,129,140,5,29,0,0,130,140,5,24,0,0,131,140,
5,31,0,0,132,140,5,25,0,0,133,140,5,26,0,0,134,140,5,30,0,0,135,140,3,14,
7,0,136,140,5,32,0,0,137,140,3,18,9,0,138,140,3,20,10,0,139,127,1,0,0,0,
139,128,1,0,0,0,139,129,1,0,0,0,139,130,1,0,0,0,139,131,1,0,0,0,139,132,
1,0,0,0,139,133,1,0,0,0,139,134,1,0,0,0,139,135,1,0,0,0,139,136,1,0,0,0,
139,137,1,0,0,0,139,138,1,0,0,0,140,17,1,0,0,0,141,143,5,21,0,0,142,144,
5,1,0,0,143,142,1,0,0,0,143,144,1,0,0,0,144,145,1,0,0,0,145,153,3,16,8,0,
146,148,5,22,0,0,147,149,5,1,0,0,148,147,1,0,0,0,148,149,1,0,0,0,149,150,
1,0,0,0,150,152,3,16,8,0,151,146,1,0,0,0,152,155,1,0,0,0,153,151,1,0,0,0,
153,154,1,0,0,0,154,156,1,0,0,0,155,153,1,0,0,0,156,157,5,23,0,0,157,19,
1,0,0,0,158,159,5,24,0,0,159,160,5,3,0,0,160,161,3,16,8,0,161,162,5,4,0,
0,162,21,1,0,0,0,14,25,31,38,51,68,80,100,110,115,122,139,143,148,153];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class AxolangParser extends antlr4.Parser {

    static grammarFileName = "Axolang.g4";
    static literalNames = [ null, "' '", "'='", "'['", "']'", "'xxsvar'", 
                            "'xsvar'", "'svar'", "'var'", "'lvar'", "'xlvar'", 
                            "'xxlvar'", "'fun'", "'match'", "'('", "')'", 
                            "'{'", "'}'", "'->'", "';'", "'_'", "'\\u00AB'", 
                            "','", "'\\u00BB'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             "IDENTIFIER", "CHAR_LITERAL", "STRING_LITERAL", 
                             "INT_LITERAL", "UINT_LITERAL", "FLOAT_LITERAL", 
                             "DECIMAL_LITERAL", "COMPLEX_LITERAL", "BOOLEAN", 
                             "WS", "OTHER" ];
    static ruleNames = [ "program", "statement", "varDeclaration", "type", 
                         "matchStatement", "matchCase", "declaration", "pkg", 
                         "expression", "arrayLiteral", "arrayAccess" ];

    constructor(input) {
        super(input);
        this._interp = new antlr4.atn.ParserATNSimulator(this, atn, decisionsToDFA, sharedContextCache);
        this.ruleNames = AxolangParser.ruleNames;
        this.literalNames = AxolangParser.literalNames;
        this.symbolicNames = AxolangParser.symbolicNames;
    }



	program() {
	    let localctx = new ProgramContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 0, AxolangParser.RULE_program);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 25;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,0,this._ctx)
	        while(_alt!=1 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1+1) {
	                this.state = 22;
	                this.match(AxolangParser.T__0); 
	            }
	            this.state = 27;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,0,this._ctx);
	        }

	        this.state = 31;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 16352) !== 0)) {
	            this.state = 28;
	            this.statement();
	            this.state = 33;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 34;
	        this.match(AxolangParser.EOF);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	statement() {
	    let localctx = new StatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 2, AxolangParser.RULE_statement);
	    try {
	        this.state = 38;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 5:
	        case 6:
	        case 7:
	        case 8:
	        case 9:
	        case 10:
	        case 11:
	        case 12:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 36;
	            this.varDeclaration();
	            break;
	        case 13:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 37;
	            this.matchStatement();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	varDeclaration() {
	    let localctx = new VarDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 4, AxolangParser.RULE_varDeclaration);
	    var _la = 0;
	    try {
	        this.state = 68;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,4,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 40;
	            this.type();
	            this.state = 41;
	            this.match(AxolangParser.T__0);
	            this.state = 42;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 43;
	            this.match(AxolangParser.T__1);
	            this.state = 44;
	            this.expression();
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 46;
	            this.type();
	            this.state = 47;
	            this.match(AxolangParser.T__0);
	            this.state = 48;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 49;
	            this.match(AxolangParser.T__2);
	            this.state = 51;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===27) {
	                this.state = 50;
	                this.match(AxolangParser.INT_LITERAL);
	            }

	            this.state = 53;
	            this.match(AxolangParser.T__3);
	            this.state = 54;
	            this.match(AxolangParser.T__1);
	            this.state = 55;
	            this.arrayLiteral();
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 57;
	            this.type();
	            this.state = 58;
	            this.match(AxolangParser.T__0);
	            this.state = 59;
	            this.match(AxolangParser.IDENTIFIER);
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 61;
	            this.type();
	            this.state = 62;
	            this.match(AxolangParser.T__0);
	            this.state = 63;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 64;
	            this.match(AxolangParser.T__2);
	            this.state = 65;
	            this.match(AxolangParser.INT_LITERAL);
	            this.state = 66;
	            this.match(AxolangParser.T__3);
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	type() {
	    let localctx = new TypeContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 6, AxolangParser.RULE_type);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 70;
	        _la = this._input.LA(1);
	        if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 8160) !== 0))) {
	        this._errHandler.recoverInline(this);
	        }
	        else {
	        	this._errHandler.reportMatch(this);
	            this.consume();
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	matchStatement() {
	    let localctx = new MatchStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 8, AxolangParser.RULE_matchStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 72;
	        this.match(AxolangParser.T__12);
	        this.state = 73;
	        this.match(AxolangParser.T__13);
	        this.state = 74;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 75;
	        this.match(AxolangParser.T__14);
	        this.state = 76;
	        this.match(AxolangParser.T__15);
	        this.state = 78; 
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        do {
	            this.state = 77;
	            this.matchCase();
	            this.state = 80; 
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        } while(((((_la - 1)) & ~0x1f) === 0 && ((1 << (_la - 1)) & 4288184321) !== 0));
	        this.state = 82;
	        this.match(AxolangParser.T__16);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	matchCase() {
	    let localctx = new MatchCaseContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 10, AxolangParser.RULE_matchCase);
	    try {
	        this.state = 100;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,6,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 84;
	            this.expression();
	            this.state = 85;
	            this.match(AxolangParser.T__17);
	            this.state = 86;
	            this.declaration();
	            this.state = 87;
	            this.match(AxolangParser.T__18);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 89;
	            this.expression();
	            this.state = 90;
	            this.match(AxolangParser.T__17);
	            this.state = 91;
	            this.match(AxolangParser.T__15);
	            this.state = 92;
	            this.match(AxolangParser.OTHER);
	            this.state = 93;
	            this.match(AxolangParser.T__16);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 95;
	            this.match(AxolangParser.T__19);
	            this.state = 96;
	            this.match(AxolangParser.T__17);
	            this.state = 97;
	            this.declaration();
	            this.state = 98;
	            this.match(AxolangParser.T__18);
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	declaration() {
	    let localctx = new DeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 12, AxolangParser.RULE_declaration);
	    try {
	        this.state = 110;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,7,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 102;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 103;
	            this.match(AxolangParser.T__1);
	            this.state = 104;
	            this.expression();
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 105;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 106;
	            this.match(AxolangParser.T__13);
	            this.state = 107;
	            this.match(AxolangParser.OTHER);
	            this.state = 108;
	            this.match(AxolangParser.T__14);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 109;
	            this.statement();
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	pkg() {
	    let localctx = new PkgContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 14, AxolangParser.RULE_pkg);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 115;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,8,this._ctx)
	        while(_alt!=1 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1+1) {
	                this.state = 112;
	                this.match(AxolangParser.T__0); 
	            }
	            this.state = 117;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,8,this._ctx);
	        }

	        this.state = 118;
	        this.match(AxolangParser.T__15);
	        this.state = 122;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 8160) !== 0)) {
	            this.state = 119;
	            this.varDeclaration();
	            this.state = 124;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 125;
	        this.match(AxolangParser.T__16);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	expression() {
	    let localctx = new ExpressionContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 16, AxolangParser.RULE_expression);
	    try {
	        this.state = 139;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,10,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 127;
	            this.match(AxolangParser.INT_LITERAL);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 128;
	            this.match(AxolangParser.UINT_LITERAL);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 129;
	            this.match(AxolangParser.FLOAT_LITERAL);
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 130;
	            this.match(AxolangParser.IDENTIFIER);
	            break;

	        case 5:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 131;
	            this.match(AxolangParser.COMPLEX_LITERAL);
	            break;

	        case 6:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 132;
	            this.match(AxolangParser.CHAR_LITERAL);
	            break;

	        case 7:
	            this.enterOuterAlt(localctx, 7);
	            this.state = 133;
	            this.match(AxolangParser.STRING_LITERAL);
	            break;

	        case 8:
	            this.enterOuterAlt(localctx, 8);
	            this.state = 134;
	            this.match(AxolangParser.DECIMAL_LITERAL);
	            break;

	        case 9:
	            this.enterOuterAlt(localctx, 9);
	            this.state = 135;
	            this.pkg();
	            break;

	        case 10:
	            this.enterOuterAlt(localctx, 10);
	            this.state = 136;
	            this.match(AxolangParser.BOOLEAN);
	            break;

	        case 11:
	            this.enterOuterAlt(localctx, 11);
	            this.state = 137;
	            this.arrayLiteral();
	            break;

	        case 12:
	            this.enterOuterAlt(localctx, 12);
	            this.state = 138;
	            this.arrayAccess();
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	arrayLiteral() {
	    let localctx = new ArrayLiteralContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, AxolangParser.RULE_arrayLiteral);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 141;
	        this.match(AxolangParser.T__20);
	        this.state = 143;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,11,this._ctx);
	        if(la_===1) {
	            this.state = 142;
	            this.match(AxolangParser.T__0);

	        }
	        this.state = 145;
	        this.expression();
	        this.state = 153;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(_la===22) {
	            this.state = 146;
	            this.match(AxolangParser.T__21);
	            this.state = 148;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,12,this._ctx);
	            if(la_===1) {
	                this.state = 147;
	                this.match(AxolangParser.T__0);

	            }
	            this.state = 150;
	            this.expression();
	            this.state = 155;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 156;
	        this.match(AxolangParser.T__22);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	arrayAccess() {
	    let localctx = new ArrayAccessContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 20, AxolangParser.RULE_arrayAccess);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 158;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 159;
	        this.match(AxolangParser.T__2);
	        this.state = 160;
	        this.expression();
	        this.state = 161;
	        this.match(AxolangParser.T__3);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


}

AxolangParser.EOF = antlr4.Token.EOF;
AxolangParser.T__0 = 1;
AxolangParser.T__1 = 2;
AxolangParser.T__2 = 3;
AxolangParser.T__3 = 4;
AxolangParser.T__4 = 5;
AxolangParser.T__5 = 6;
AxolangParser.T__6 = 7;
AxolangParser.T__7 = 8;
AxolangParser.T__8 = 9;
AxolangParser.T__9 = 10;
AxolangParser.T__10 = 11;
AxolangParser.T__11 = 12;
AxolangParser.T__12 = 13;
AxolangParser.T__13 = 14;
AxolangParser.T__14 = 15;
AxolangParser.T__15 = 16;
AxolangParser.T__16 = 17;
AxolangParser.T__17 = 18;
AxolangParser.T__18 = 19;
AxolangParser.T__19 = 20;
AxolangParser.T__20 = 21;
AxolangParser.T__21 = 22;
AxolangParser.T__22 = 23;
AxolangParser.IDENTIFIER = 24;
AxolangParser.CHAR_LITERAL = 25;
AxolangParser.STRING_LITERAL = 26;
AxolangParser.INT_LITERAL = 27;
AxolangParser.UINT_LITERAL = 28;
AxolangParser.FLOAT_LITERAL = 29;
AxolangParser.DECIMAL_LITERAL = 30;
AxolangParser.COMPLEX_LITERAL = 31;
AxolangParser.BOOLEAN = 32;
AxolangParser.WS = 33;
AxolangParser.OTHER = 34;

AxolangParser.RULE_program = 0;
AxolangParser.RULE_statement = 1;
AxolangParser.RULE_varDeclaration = 2;
AxolangParser.RULE_type = 3;
AxolangParser.RULE_matchStatement = 4;
AxolangParser.RULE_matchCase = 5;
AxolangParser.RULE_declaration = 6;
AxolangParser.RULE_pkg = 7;
AxolangParser.RULE_expression = 8;
AxolangParser.RULE_arrayLiteral = 9;
AxolangParser.RULE_arrayAccess = 10;

class ProgramContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_program;
    }

	EOF() {
	    return this.getToken(AxolangParser.EOF, 0);
	};

	statement = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(StatementContext);
	    } else {
	        return this.getTypedRuleContext(StatementContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterProgram(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitProgram(this);
		}
	}


}



class StatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_statement;
    }

	varDeclaration() {
	    return this.getTypedRuleContext(VarDeclarationContext,0);
	};

	matchStatement() {
	    return this.getTypedRuleContext(MatchStatementContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitStatement(this);
		}
	}


}



class VarDeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_varDeclaration;
    }

	type() {
	    return this.getTypedRuleContext(TypeContext,0);
	};

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	arrayLiteral() {
	    return this.getTypedRuleContext(ArrayLiteralContext,0);
	};

	INT_LITERAL() {
	    return this.getToken(AxolangParser.INT_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterVarDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitVarDeclaration(this);
		}
	}


}



class TypeContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_type;
    }


	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterType(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitType(this);
		}
	}


}



class MatchStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_matchStatement;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	matchCase = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(MatchCaseContext);
	    } else {
	        return this.getTypedRuleContext(MatchCaseContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterMatchStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitMatchStatement(this);
		}
	}


}



class MatchCaseContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_matchCase;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	declaration() {
	    return this.getTypedRuleContext(DeclarationContext,0);
	};

	OTHER() {
	    return this.getToken(AxolangParser.OTHER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterMatchCase(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitMatchCase(this);
		}
	}


}



class DeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_declaration;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	OTHER() {
	    return this.getToken(AxolangParser.OTHER, 0);
	};

	statement() {
	    return this.getTypedRuleContext(StatementContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitDeclaration(this);
		}
	}


}



class PkgContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_pkg;
    }

	varDeclaration = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(VarDeclarationContext);
	    } else {
	        return this.getTypedRuleContext(VarDeclarationContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterPkg(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitPkg(this);
		}
	}


}



class ExpressionContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_expression;
    }

	INT_LITERAL() {
	    return this.getToken(AxolangParser.INT_LITERAL, 0);
	};

	UINT_LITERAL() {
	    return this.getToken(AxolangParser.UINT_LITERAL, 0);
	};

	FLOAT_LITERAL() {
	    return this.getToken(AxolangParser.FLOAT_LITERAL, 0);
	};

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	COMPLEX_LITERAL() {
	    return this.getToken(AxolangParser.COMPLEX_LITERAL, 0);
	};

	CHAR_LITERAL() {
	    return this.getToken(AxolangParser.CHAR_LITERAL, 0);
	};

	STRING_LITERAL() {
	    return this.getToken(AxolangParser.STRING_LITERAL, 0);
	};

	DECIMAL_LITERAL() {
	    return this.getToken(AxolangParser.DECIMAL_LITERAL, 0);
	};

	pkg() {
	    return this.getTypedRuleContext(PkgContext,0);
	};

	BOOLEAN() {
	    return this.getToken(AxolangParser.BOOLEAN, 0);
	};

	arrayLiteral() {
	    return this.getTypedRuleContext(ArrayLiteralContext,0);
	};

	arrayAccess() {
	    return this.getTypedRuleContext(ArrayAccessContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterExpression(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitExpression(this);
		}
	}


}



class ArrayLiteralContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_arrayLiteral;
    }

	expression = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(ExpressionContext);
	    } else {
	        return this.getTypedRuleContext(ExpressionContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterArrayLiteral(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitArrayLiteral(this);
		}
	}


}



class ArrayAccessContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_arrayAccess;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterArrayAccess(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitArrayAccess(this);
		}
	}


}




AxolangParser.ProgramContext = ProgramContext; 
AxolangParser.StatementContext = StatementContext; 
AxolangParser.VarDeclarationContext = VarDeclarationContext; 
AxolangParser.TypeContext = TypeContext; 
AxolangParser.MatchStatementContext = MatchStatementContext; 
AxolangParser.MatchCaseContext = MatchCaseContext; 
AxolangParser.DeclarationContext = DeclarationContext; 
AxolangParser.PkgContext = PkgContext; 
AxolangParser.ExpressionContext = ExpressionContext; 
AxolangParser.ArrayLiteralContext = ArrayLiteralContext; 
AxolangParser.ArrayAccessContext = ArrayAccessContext; 
