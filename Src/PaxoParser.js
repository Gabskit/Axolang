// jshint ignore: start
import antlr4 from 'antlr4';
import PaxoListener from './PaxoListener.js';
const serializedATN = [4,1,59,255,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,
2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,5,0,38,8,0,10,0,12,
0,41,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,3,1,61,8,1,1,1,3,1,64,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,
2,75,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,90,8,2,
1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,101,8,4,1,5,1,5,1,5,1,5,1,5,1,5,
1,5,3,5,110,8,5,1,6,1,6,1,6,1,6,1,6,1,6,4,6,118,8,6,11,6,12,6,119,1,6,1,
6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,131,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,148,8,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,
1,10,3,10,158,8,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,5,11,169,
8,11,10,11,12,11,172,9,11,1,11,1,11,1,12,1,12,5,12,178,8,12,10,12,12,12,
181,9,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,5,13,191,8,13,10,13,12,
13,194,9,13,1,14,1,14,1,14,5,14,199,8,14,10,14,12,14,202,9,14,1,15,1,15,
1,15,1,15,3,15,208,8,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,
1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,229,8,15,1,15,1,15,1,15,
5,15,234,8,15,10,15,12,15,237,9,15,1,16,1,16,1,16,1,16,5,16,243,8,16,10,
16,12,16,246,9,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,0,1,30,18,0,2,
4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,0,3,1,0,9,14,1,0,28,29,3,0,
3,3,5,5,35,38,284,0,39,1,0,0,0,2,63,1,0,0,0,4,89,1,0,0,0,6,91,1,0,0,0,8,
100,1,0,0,0,10,102,1,0,0,0,12,111,1,0,0,0,14,130,1,0,0,0,16,132,1,0,0,0,
18,140,1,0,0,0,20,152,1,0,0,0,22,162,1,0,0,0,24,175,1,0,0,0,26,184,1,0,0,
0,28,195,1,0,0,0,30,228,1,0,0,0,32,238,1,0,0,0,34,249,1,0,0,0,36,38,3,2,
1,0,37,36,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,42,1,0,0,
0,41,39,1,0,0,0,42,43,5,0,0,1,43,1,1,0,0,0,44,64,3,4,2,0,45,64,3,8,4,0,46,
64,3,12,6,0,47,64,3,10,5,0,48,64,3,16,8,0,49,64,3,18,9,0,50,64,3,20,10,0,
51,64,3,22,11,0,52,53,3,30,15,0,53,54,5,1,0,0,54,64,1,0,0,0,55,56,5,2,0,
0,56,57,5,3,0,0,57,60,5,56,0,0,58,59,5,4,0,0,59,61,5,56,0,0,60,58,1,0,0,
0,60,61,1,0,0,0,61,62,1,0,0,0,62,64,5,5,0,0,63,44,1,0,0,0,63,45,1,0,0,0,
63,46,1,0,0,0,63,47,1,0,0,0,63,48,1,0,0,0,63,49,1,0,0,0,63,50,1,0,0,0,63,
51,1,0,0,0,63,52,1,0,0,0,63,55,1,0,0,0,64,3,1,0,0,0,65,66,3,6,3,0,66,67,
5,56,0,0,67,68,5,6,0,0,68,69,3,30,15,0,69,90,1,0,0,0,70,71,3,6,3,0,71,72,
5,56,0,0,72,74,5,7,0,0,73,75,5,41,0,0,74,73,1,0,0,0,74,75,1,0,0,0,75,76,
1,0,0,0,76,77,5,8,0,0,77,78,5,6,0,0,78,79,3,32,16,0,79,90,1,0,0,0,80,81,
3,6,3,0,81,82,5,56,0,0,82,90,1,0,0,0,83,84,3,6,3,0,84,85,5,56,0,0,85,86,
5,7,0,0,86,87,5,41,0,0,87,88,5,8,0,0,88,90,1,0,0,0,89,65,1,0,0,0,89,70,1,
0,0,0,89,80,1,0,0,0,89,83,1,0,0,0,90,5,1,0,0,0,91,92,7,0,0,0,92,7,1,0,0,
0,93,94,5,56,0,0,94,95,5,6,0,0,95,101,3,30,15,0,96,97,5,56,0,0,97,101,5,
15,0,0,98,99,5,56,0,0,99,101,5,16,0,0,100,93,1,0,0,0,100,96,1,0,0,0,100,
98,1,0,0,0,101,9,1,0,0,0,102,103,5,17,0,0,103,104,5,18,0,0,104,105,3,30,
15,0,105,106,5,19,0,0,106,109,3,24,12,0,107,108,5,20,0,0,108,110,3,24,12,
0,109,107,1,0,0,0,109,110,1,0,0,0,110,11,1,0,0,0,111,112,5,21,0,0,112,113,
5,18,0,0,113,114,5,56,0,0,114,115,5,19,0,0,115,117,5,22,0,0,116,118,3,14,
7,0,117,116,1,0,0,0,118,119,1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,
121,1,0,0,0,121,122,5,23,0,0,122,13,1,0,0,0,123,124,3,30,15,0,124,125,5,
24,0,0,125,126,3,24,12,0,126,131,1,0,0,0,127,128,5,25,0,0,128,129,5,24,0,
0,129,131,3,24,12,0,130,123,1,0,0,0,130,127,1,0,0,0,131,15,1,0,0,0,132,133,
5,26,0,0,133,134,5,18,0,0,134,135,3,30,15,0,135,136,5,19,0,0,136,137,5,27,
0,0,137,138,7,1,0,0,138,139,3,24,12,0,139,17,1,0,0,0,140,141,5,30,0,0,141,
142,3,24,12,0,142,143,5,31,0,0,143,144,5,18,0,0,144,147,5,56,0,0,145,146,
5,4,0,0,146,148,5,56,0,0,147,145,1,0,0,0,147,148,1,0,0,0,148,149,1,0,0,0,
149,150,5,19,0,0,150,151,3,24,12,0,151,19,1,0,0,0,152,153,5,32,0,0,153,154,
5,56,0,0,154,155,5,6,0,0,155,157,5,18,0,0,156,158,3,26,13,0,157,156,1,0,
0,0,157,158,1,0,0,0,158,159,1,0,0,0,159,160,5,19,0,0,160,161,3,24,12,0,161,
21,1,0,0,0,162,163,5,33,0,0,163,164,5,56,0,0,164,165,5,6,0,0,165,170,5,22,
0,0,166,169,3,4,2,0,167,169,3,20,10,0,168,166,1,0,0,0,168,167,1,0,0,0,169,
172,1,0,0,0,170,168,1,0,0,0,170,171,1,0,0,0,171,173,1,0,0,0,172,170,1,0,
0,0,173,174,5,23,0,0,174,23,1,0,0,0,175,179,5,22,0,0,176,178,3,2,1,0,177,
176,1,0,0,0,178,181,1,0,0,0,179,177,1,0,0,0,179,180,1,0,0,0,180,182,1,0,
0,0,181,179,1,0,0,0,182,183,5,23,0,0,183,25,1,0,0,0,184,185,3,6,3,0,185,
192,5,56,0,0,186,187,5,34,0,0,187,188,3,6,3,0,188,189,5,56,0,0,189,191,1,
0,0,0,190,186,1,0,0,0,191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,
27,1,0,0,0,194,192,1,0,0,0,195,200,3,30,15,0,196,197,5,34,0,0,197,199,3,
30,15,0,198,196,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,0,200,201,1,0,0,0,
201,29,1,0,0,0,202,200,1,0,0,0,203,204,6,15,-1,0,204,205,5,56,0,0,205,207,
5,18,0,0,206,208,3,28,14,0,207,206,1,0,0,0,207,208,1,0,0,0,208,209,1,0,0,
0,209,229,5,19,0,0,210,229,5,41,0,0,211,229,5,42,0,0,212,229,5,43,0,0,213,
229,5,44,0,0,214,229,5,45,0,0,215,229,5,46,0,0,216,229,5,52,0,0,217,229,
5,53,0,0,218,229,5,54,0,0,219,229,5,55,0,0,220,229,5,47,0,0,221,229,5,48,
0,0,222,229,5,49,0,0,223,229,5,50,0,0,224,229,5,51,0,0,225,229,3,32,16,0,
226,229,3,34,17,0,227,229,5,56,0,0,228,203,1,0,0,0,228,210,1,0,0,0,228,211,
1,0,0,0,228,212,1,0,0,0,228,213,1,0,0,0,228,214,1,0,0,0,228,215,1,0,0,0,
228,216,1,0,0,0,228,217,1,0,0,0,228,218,1,0,0,0,228,219,1,0,0,0,228,220,
1,0,0,0,228,221,1,0,0,0,228,222,1,0,0,0,228,223,1,0,0,0,228,224,1,0,0,0,
228,225,1,0,0,0,228,226,1,0,0,0,228,227,1,0,0,0,229,235,1,0,0,0,230,231,
10,20,0,0,231,232,7,2,0,0,232,234,3,30,15,21,233,230,1,0,0,0,234,237,1,0,
0,0,235,233,1,0,0,0,235,236,1,0,0,0,236,31,1,0,0,0,237,235,1,0,0,0,238,239,
5,39,0,0,239,244,3,30,15,0,240,241,5,34,0,0,241,243,3,30,15,0,242,240,1,
0,0,0,243,246,1,0,0,0,244,242,1,0,0,0,244,245,1,0,0,0,245,247,1,0,0,0,246,
244,1,0,0,0,247,248,5,40,0,0,248,33,1,0,0,0,249,250,5,56,0,0,250,251,5,7,
0,0,251,252,3,30,15,0,252,253,5,8,0,0,253,35,1,0,0,0,20,39,60,63,74,89,100,
109,119,130,147,157,168,170,179,192,200,207,228,235,244];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class PaxoParser extends antlr4.Parser {

    static grammarFileName = "Paxo.g4";
    static literalNames = [ null, "';'", "'add'", "'<'", "'.'", "'>'", "'='", 
                            "'['", "']'", "'var'", "'xxsvar'", "'xsvar'", 
                            "'svar'", "'lvar'", "'xlvar'", "'++'", "'--'", 
                            "'if'", "'('", "')'", "'else'", "'match'", "'{'", 
                            "'}'", "'->'", "'default'", "'loop'", "':'", 
                            "'stop'", "'go'", "'try'", "'catch'", "'fun'", 
                            "'pkg'", "','", "'\\u2264'", "'\\u2265'", "'=='", 
                            "'\\u2260'", "'\\u00AB'", "'\\u00BB'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, "INT_LITERAL", "UINT_LITERAL", "FLOAT_LITERAL", 
                             "DECIMAL_LITERAL", "COMPLEX_FLT_LITERAL", "COMPLEX_DEC_LITERAL", 
                             "VECTOR2D", "VECTOR4D", "NANOTIME_LITERAL", 
                             "SLICE_LITERAL", "POINTER_LITERAL", "CHAR_LITERAL", 
                             "STRING_LITERAL", "EMSTRING_LITERAL", "BOOLEAN", 
                             "IDENTIFIER", "LINE_COMMENT", "BLOCK_COMMENT", 
                             "WS" ];
    static ruleNames = [ "program", "statement", "varDeclaration", "type", 
                         "assignment", "ifElseStatement", "matchStatement", 
                         "matchCase", "loopStatement", "tryCatchStatement", 
                         "functionDeclaration", "pkgDeclaration", "block", 
                         "parameterList", "argumentList", "expression", 
                         "arrayLiteral", "arrayAccess" ];

    constructor(input) {
        super(input);
        this._interp = new antlr4.atn.ParserATNSimulator(this, atn, decisionsToDFA, sharedContextCache);
        this.ruleNames = PaxoParser.ruleNames;
        this.literalNames = PaxoParser.literalNames;
        this.symbolicNames = PaxoParser.symbolicNames;
    }

    sempred(localctx, ruleIndex, predIndex) {
    	switch(ruleIndex) {
    	case 15:
    	    		return this.expression_sempred(localctx, predIndex);
        default:
            throw "No predicate with index:" + ruleIndex;
       }
    }

    expression_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 0:
    			return this.precpred(this._ctx, 20);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };




	program() {
	    let localctx = new ProgramContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 0, PaxoParser.RULE_program);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 39;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 1143111172) !== 0) || ((((_la - 32)) & ~0x1f) === 0 && ((1 << (_la - 32)) & 33554051) !== 0)) {
	            this.state = 36;
	            this.statement();
	            this.state = 41;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 42;
	        this.match(PaxoParser.EOF);
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
	    this.enterRule(localctx, 2, PaxoParser.RULE_statement);
	    var _la = 0;
	    try {
	        this.state = 63;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,2,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 44;
	            this.varDeclaration();
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 45;
	            this.assignment();
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 46;
	            this.matchStatement();
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 47;
	            this.ifElseStatement();
	            break;

	        case 5:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 48;
	            this.loopStatement();
	            break;

	        case 6:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 49;
	            this.tryCatchStatement();
	            break;

	        case 7:
	            this.enterOuterAlt(localctx, 7);
	            this.state = 50;
	            this.functionDeclaration();
	            break;

	        case 8:
	            this.enterOuterAlt(localctx, 8);
	            this.state = 51;
	            this.pkgDeclaration();
	            break;

	        case 9:
	            this.enterOuterAlt(localctx, 9);
	            this.state = 52;
	            this.expression(0);
	            this.state = 53;
	            this.match(PaxoParser.T__0);
	            break;

	        case 10:
	            this.enterOuterAlt(localctx, 10);
	            this.state = 55;
	            this.match(PaxoParser.T__1);
	            this.state = 56;
	            this.match(PaxoParser.T__2);
	            this.state = 57;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 60;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===4) {
	                this.state = 58;
	                this.match(PaxoParser.T__3);
	                this.state = 59;
	                this.match(PaxoParser.IDENTIFIER);
	            }

	            this.state = 62;
	            this.match(PaxoParser.T__4);
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



	varDeclaration() {
	    let localctx = new VarDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 4, PaxoParser.RULE_varDeclaration);
	    var _la = 0;
	    try {
	        this.state = 89;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,4,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 65;
	            this.type();
	            this.state = 66;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 67;
	            this.match(PaxoParser.T__5);
	            this.state = 68;
	            this.expression(0);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 70;
	            this.type();
	            this.state = 71;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 72;
	            this.match(PaxoParser.T__6);
	            this.state = 74;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===41) {
	                this.state = 73;
	                this.match(PaxoParser.INT_LITERAL);
	            }

	            this.state = 76;
	            this.match(PaxoParser.T__7);
	            this.state = 77;
	            this.match(PaxoParser.T__5);
	            this.state = 78;
	            this.arrayLiteral();
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 80;
	            this.type();
	            this.state = 81;
	            this.match(PaxoParser.IDENTIFIER);
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 83;
	            this.type();
	            this.state = 84;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 85;
	            this.match(PaxoParser.T__6);
	            this.state = 86;
	            this.match(PaxoParser.INT_LITERAL);
	            this.state = 87;
	            this.match(PaxoParser.T__7);
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
	    this.enterRule(localctx, 6, PaxoParser.RULE_type);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 91;
	        _la = this._input.LA(1);
	        if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 32256) !== 0))) {
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



	assignment() {
	    let localctx = new AssignmentContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 8, PaxoParser.RULE_assignment);
	    try {
	        this.state = 100;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,5,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 93;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 94;
	            this.match(PaxoParser.T__5);
	            this.state = 95;
	            this.expression(0);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 96;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 97;
	            this.match(PaxoParser.T__14);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 98;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 99;
	            this.match(PaxoParser.T__15);
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



	ifElseStatement() {
	    let localctx = new IfElseStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 10, PaxoParser.RULE_ifElseStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 102;
	        this.match(PaxoParser.T__16);
	        this.state = 103;
	        this.match(PaxoParser.T__17);
	        this.state = 104;
	        this.expression(0);
	        this.state = 105;
	        this.match(PaxoParser.T__18);
	        this.state = 106;
	        this.block();
	        this.state = 109;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(_la===20) {
	            this.state = 107;
	            this.match(PaxoParser.T__19);
	            this.state = 108;
	            this.block();
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
	    this.enterRule(localctx, 12, PaxoParser.RULE_matchStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 111;
	        this.match(PaxoParser.T__20);
	        this.state = 112;
	        this.match(PaxoParser.T__17);
	        this.state = 113;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 114;
	        this.match(PaxoParser.T__18);
	        this.state = 115;
	        this.match(PaxoParser.T__21);
	        this.state = 117; 
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        do {
	            this.state = 116;
	            this.matchCase();
	            this.state = 119; 
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        } while(((((_la - 25)) & ~0x1f) === 0 && ((1 << (_la - 25)) & 4294918145) !== 0));
	        this.state = 121;
	        this.match(PaxoParser.T__22);
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
	    this.enterRule(localctx, 14, PaxoParser.RULE_matchCase);
	    try {
	        this.state = 130;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 39:
	        case 41:
	        case 42:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 47:
	        case 48:
	        case 49:
	        case 50:
	        case 51:
	        case 52:
	        case 53:
	        case 54:
	        case 55:
	        case 56:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 123;
	            this.expression(0);
	            this.state = 124;
	            this.match(PaxoParser.T__23);
	            this.state = 125;
	            this.block();
	            break;
	        case 25:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 127;
	            this.match(PaxoParser.T__24);
	            this.state = 128;
	            this.match(PaxoParser.T__23);
	            this.state = 129;
	            this.block();
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



	loopStatement() {
	    let localctx = new LoopStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 16, PaxoParser.RULE_loopStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 132;
	        this.match(PaxoParser.T__25);
	        this.state = 133;
	        this.match(PaxoParser.T__17);
	        this.state = 134;
	        this.expression(0);
	        this.state = 135;
	        this.match(PaxoParser.T__18);
	        this.state = 136;
	        this.match(PaxoParser.T__26);
	        this.state = 137;
	        _la = this._input.LA(1);
	        if(!(_la===28 || _la===29)) {
	        this._errHandler.recoverInline(this);
	        }
	        else {
	        	this._errHandler.reportMatch(this);
	            this.consume();
	        }
	        this.state = 138;
	        this.block();
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



	tryCatchStatement() {
	    let localctx = new TryCatchStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, PaxoParser.RULE_tryCatchStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 140;
	        this.match(PaxoParser.T__29);
	        this.state = 141;
	        this.block();
	        this.state = 142;
	        this.match(PaxoParser.T__30);
	        this.state = 143;
	        this.match(PaxoParser.T__17);
	        this.state = 144;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 147;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(_la===4) {
	            this.state = 145;
	            this.match(PaxoParser.T__3);
	            this.state = 146;
	            this.match(PaxoParser.IDENTIFIER);
	        }

	        this.state = 149;
	        this.match(PaxoParser.T__18);
	        this.state = 150;
	        this.block();
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



	functionDeclaration() {
	    let localctx = new FunctionDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 20, PaxoParser.RULE_functionDeclaration);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 152;
	        this.match(PaxoParser.T__31);
	        this.state = 153;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 154;
	        this.match(PaxoParser.T__5);
	        this.state = 155;
	        this.match(PaxoParser.T__17);
	        this.state = 157;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if((((_la) & ~0x1f) === 0 && ((1 << _la) & 32256) !== 0)) {
	            this.state = 156;
	            this.parameterList();
	        }

	        this.state = 159;
	        this.match(PaxoParser.T__18);
	        this.state = 160;
	        this.block();
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



	pkgDeclaration() {
	    let localctx = new PkgDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 22, PaxoParser.RULE_pkgDeclaration);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 162;
	        this.match(PaxoParser.T__32);
	        this.state = 163;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 164;
	        this.match(PaxoParser.T__5);
	        this.state = 165;
	        this.match(PaxoParser.T__21);
	        this.state = 170;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(((((_la - 9)) & ~0x1f) === 0 && ((1 << (_la - 9)) & 8388671) !== 0)) {
	            this.state = 168;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 9:
	            case 10:
	            case 11:
	            case 12:
	            case 13:
	            case 14:
	                this.state = 166;
	                this.varDeclaration();
	                break;
	            case 32:
	                this.state = 167;
	                this.functionDeclaration();
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 172;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 173;
	        this.match(PaxoParser.T__22);
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



	block() {
	    let localctx = new BlockContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 24, PaxoParser.RULE_block);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 175;
	        this.match(PaxoParser.T__21);
	        this.state = 179;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 1143111172) !== 0) || ((((_la - 32)) & ~0x1f) === 0 && ((1 << (_la - 32)) & 33554051) !== 0)) {
	            this.state = 176;
	            this.statement();
	            this.state = 181;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 182;
	        this.match(PaxoParser.T__22);
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



	parameterList() {
	    let localctx = new ParameterListContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 26, PaxoParser.RULE_parameterList);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 184;
	        this.type();
	        this.state = 185;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 192;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(_la===34) {
	            this.state = 186;
	            this.match(PaxoParser.T__33);
	            this.state = 187;
	            this.type();
	            this.state = 188;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 194;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
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



	argumentList() {
	    let localctx = new ArgumentListContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 28, PaxoParser.RULE_argumentList);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 195;
	        this.expression(0);
	        this.state = 200;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(_la===34) {
	            this.state = 196;
	            this.match(PaxoParser.T__33);
	            this.state = 197;
	            this.expression(0);
	            this.state = 202;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
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


	expression(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new ExpressionContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 30;
	    this.enterRecursionRule(localctx, 30, PaxoParser.RULE_expression, _p);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 228;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,17,this._ctx);
	        switch(la_) {
	        case 1:
	            this.state = 204;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 205;
	            this.match(PaxoParser.T__17);
	            this.state = 207;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(((((_la - 39)) & ~0x1f) === 0 && ((1 << (_la - 39)) & 262141) !== 0)) {
	                this.state = 206;
	                this.argumentList();
	            }

	            this.state = 209;
	            this.match(PaxoParser.T__18);
	            break;

	        case 2:
	            this.state = 210;
	            this.match(PaxoParser.INT_LITERAL);
	            break;

	        case 3:
	            this.state = 211;
	            this.match(PaxoParser.UINT_LITERAL);
	            break;

	        case 4:
	            this.state = 212;
	            this.match(PaxoParser.FLOAT_LITERAL);
	            break;

	        case 5:
	            this.state = 213;
	            this.match(PaxoParser.DECIMAL_LITERAL);
	            break;

	        case 6:
	            this.state = 214;
	            this.match(PaxoParser.COMPLEX_FLT_LITERAL);
	            break;

	        case 7:
	            this.state = 215;
	            this.match(PaxoParser.COMPLEX_DEC_LITERAL);
	            break;

	        case 8:
	            this.state = 216;
	            this.match(PaxoParser.CHAR_LITERAL);
	            break;

	        case 9:
	            this.state = 217;
	            this.match(PaxoParser.STRING_LITERAL);
	            break;

	        case 10:
	            this.state = 218;
	            this.match(PaxoParser.EMSTRING_LITERAL);
	            break;

	        case 11:
	            this.state = 219;
	            this.match(PaxoParser.BOOLEAN);
	            break;

	        case 12:
	            this.state = 220;
	            this.match(PaxoParser.VECTOR2D);
	            break;

	        case 13:
	            this.state = 221;
	            this.match(PaxoParser.VECTOR4D);
	            break;

	        case 14:
	            this.state = 222;
	            this.match(PaxoParser.NANOTIME_LITERAL);
	            break;

	        case 15:
	            this.state = 223;
	            this.match(PaxoParser.SLICE_LITERAL);
	            break;

	        case 16:
	            this.state = 224;
	            this.match(PaxoParser.POINTER_LITERAL);
	            break;

	        case 17:
	            this.state = 225;
	            this.arrayLiteral();
	            break;

	        case 18:
	            this.state = 226;
	            this.arrayAccess();
	            break;

	        case 19:
	            this.state = 227;
	            this.match(PaxoParser.IDENTIFIER);
	            break;

	        }
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 235;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,18,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new ExpressionContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                this.state = 230;
	                if (!( this.precpred(this._ctx, 20))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 20)");
	                }
	                this.state = 231;
	                _la = this._input.LA(1);
	                if(!(_la===3 || _la===5 || ((((_la - 35)) & ~0x1f) === 0 && ((1 << (_la - 35)) & 15) !== 0))) {
	                this._errHandler.recoverInline(this);
	                }
	                else {
	                	this._errHandler.reportMatch(this);
	                    this.consume();
	                }
	                this.state = 232;
	                this.expression(21); 
	            }
	            this.state = 237;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,18,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}



	arrayLiteral() {
	    let localctx = new ArrayLiteralContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 32, PaxoParser.RULE_arrayLiteral);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 238;
	        this.match(PaxoParser.T__38);
	        this.state = 239;
	        this.expression(0);
	        this.state = 244;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(_la===34) {
	            this.state = 240;
	            this.match(PaxoParser.T__33);
	            this.state = 241;
	            this.expression(0);
	            this.state = 246;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 247;
	        this.match(PaxoParser.T__39);
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
	    this.enterRule(localctx, 34, PaxoParser.RULE_arrayAccess);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 249;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 250;
	        this.match(PaxoParser.T__6);
	        this.state = 251;
	        this.expression(0);
	        this.state = 252;
	        this.match(PaxoParser.T__7);
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

PaxoParser.EOF = antlr4.Token.EOF;
PaxoParser.T__0 = 1;
PaxoParser.T__1 = 2;
PaxoParser.T__2 = 3;
PaxoParser.T__3 = 4;
PaxoParser.T__4 = 5;
PaxoParser.T__5 = 6;
PaxoParser.T__6 = 7;
PaxoParser.T__7 = 8;
PaxoParser.T__8 = 9;
PaxoParser.T__9 = 10;
PaxoParser.T__10 = 11;
PaxoParser.T__11 = 12;
PaxoParser.T__12 = 13;
PaxoParser.T__13 = 14;
PaxoParser.T__14 = 15;
PaxoParser.T__15 = 16;
PaxoParser.T__16 = 17;
PaxoParser.T__17 = 18;
PaxoParser.T__18 = 19;
PaxoParser.T__19 = 20;
PaxoParser.T__20 = 21;
PaxoParser.T__21 = 22;
PaxoParser.T__22 = 23;
PaxoParser.T__23 = 24;
PaxoParser.T__24 = 25;
PaxoParser.T__25 = 26;
PaxoParser.T__26 = 27;
PaxoParser.T__27 = 28;
PaxoParser.T__28 = 29;
PaxoParser.T__29 = 30;
PaxoParser.T__30 = 31;
PaxoParser.T__31 = 32;
PaxoParser.T__32 = 33;
PaxoParser.T__33 = 34;
PaxoParser.T__34 = 35;
PaxoParser.T__35 = 36;
PaxoParser.T__36 = 37;
PaxoParser.T__37 = 38;
PaxoParser.T__38 = 39;
PaxoParser.T__39 = 40;
PaxoParser.INT_LITERAL = 41;
PaxoParser.UINT_LITERAL = 42;
PaxoParser.FLOAT_LITERAL = 43;
PaxoParser.DECIMAL_LITERAL = 44;
PaxoParser.COMPLEX_FLT_LITERAL = 45;
PaxoParser.COMPLEX_DEC_LITERAL = 46;
PaxoParser.VECTOR2D = 47;
PaxoParser.VECTOR4D = 48;
PaxoParser.NANOTIME_LITERAL = 49;
PaxoParser.SLICE_LITERAL = 50;
PaxoParser.POINTER_LITERAL = 51;
PaxoParser.CHAR_LITERAL = 52;
PaxoParser.STRING_LITERAL = 53;
PaxoParser.EMSTRING_LITERAL = 54;
PaxoParser.BOOLEAN = 55;
PaxoParser.IDENTIFIER = 56;
PaxoParser.LINE_COMMENT = 57;
PaxoParser.BLOCK_COMMENT = 58;
PaxoParser.WS = 59;

PaxoParser.RULE_program = 0;
PaxoParser.RULE_statement = 1;
PaxoParser.RULE_varDeclaration = 2;
PaxoParser.RULE_type = 3;
PaxoParser.RULE_assignment = 4;
PaxoParser.RULE_ifElseStatement = 5;
PaxoParser.RULE_matchStatement = 6;
PaxoParser.RULE_matchCase = 7;
PaxoParser.RULE_loopStatement = 8;
PaxoParser.RULE_tryCatchStatement = 9;
PaxoParser.RULE_functionDeclaration = 10;
PaxoParser.RULE_pkgDeclaration = 11;
PaxoParser.RULE_block = 12;
PaxoParser.RULE_parameterList = 13;
PaxoParser.RULE_argumentList = 14;
PaxoParser.RULE_expression = 15;
PaxoParser.RULE_arrayLiteral = 16;
PaxoParser.RULE_arrayAccess = 17;

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
        this.ruleIndex = PaxoParser.RULE_program;
    }

	EOF() {
	    return this.getToken(PaxoParser.EOF, 0);
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
	    if(listener instanceof PaxoListener ) {
	        listener.enterProgram(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_statement;
    }

	varDeclaration() {
	    return this.getTypedRuleContext(VarDeclarationContext,0);
	};

	assignment() {
	    return this.getTypedRuleContext(AssignmentContext,0);
	};

	matchStatement() {
	    return this.getTypedRuleContext(MatchStatementContext,0);
	};

	ifElseStatement() {
	    return this.getTypedRuleContext(IfElseStatementContext,0);
	};

	loopStatement() {
	    return this.getTypedRuleContext(LoopStatementContext,0);
	};

	tryCatchStatement() {
	    return this.getTypedRuleContext(TryCatchStatementContext,0);
	};

	functionDeclaration() {
	    return this.getTypedRuleContext(FunctionDeclarationContext,0);
	};

	pkgDeclaration() {
	    return this.getTypedRuleContext(PkgDeclarationContext,0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	IDENTIFIER = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(PaxoParser.IDENTIFIER);
	    } else {
	        return this.getToken(PaxoParser.IDENTIFIER, i);
	    }
	};


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_varDeclaration;
    }

	type() {
	    return this.getTypedRuleContext(TypeContext,0);
	};

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	arrayLiteral() {
	    return this.getTypedRuleContext(ArrayLiteralContext,0);
	};

	INT_LITERAL() {
	    return this.getToken(PaxoParser.INT_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterVarDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_type;
    }


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterType(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitType(this);
		}
	}


}



class AssignmentContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_assignment;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterAssignment(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitAssignment(this);
		}
	}


}



class IfElseStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_ifElseStatement;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	block = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(BlockContext);
	    } else {
	        return this.getTypedRuleContext(BlockContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterIfElseStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitIfElseStatement(this);
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
        this.ruleIndex = PaxoParser.RULE_matchStatement;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
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
	    if(listener instanceof PaxoListener ) {
	        listener.enterMatchStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_matchCase;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	block() {
	    return this.getTypedRuleContext(BlockContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterMatchCase(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitMatchCase(this);
		}
	}


}



class LoopStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_loopStatement;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	block() {
	    return this.getTypedRuleContext(BlockContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterLoopStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitLoopStatement(this);
		}
	}


}



class TryCatchStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_tryCatchStatement;
    }

	block = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(BlockContext);
	    } else {
	        return this.getTypedRuleContext(BlockContext,i);
	    }
	};

	IDENTIFIER = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(PaxoParser.IDENTIFIER);
	    } else {
	        return this.getToken(PaxoParser.IDENTIFIER, i);
	    }
	};


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterTryCatchStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitTryCatchStatement(this);
		}
	}


}



class FunctionDeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_functionDeclaration;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	block() {
	    return this.getTypedRuleContext(BlockContext,0);
	};

	parameterList() {
	    return this.getTypedRuleContext(ParameterListContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterFunctionDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitFunctionDeclaration(this);
		}
	}


}



class PkgDeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_pkgDeclaration;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

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

	functionDeclaration = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(FunctionDeclarationContext);
	    } else {
	        return this.getTypedRuleContext(FunctionDeclarationContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterPkgDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitPkgDeclaration(this);
		}
	}


}



class BlockContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_block;
    }

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
	    if(listener instanceof PaxoListener ) {
	        listener.enterBlock(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitBlock(this);
		}
	}


}



class ParameterListContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_parameterList;
    }

	type = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(TypeContext);
	    } else {
	        return this.getTypedRuleContext(TypeContext,i);
	    }
	};

	IDENTIFIER = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(PaxoParser.IDENTIFIER);
	    } else {
	        return this.getToken(PaxoParser.IDENTIFIER, i);
	    }
	};


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterParameterList(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitParameterList(this);
		}
	}


}



class ArgumentListContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_argumentList;
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
	    if(listener instanceof PaxoListener ) {
	        listener.enterArgumentList(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitArgumentList(this);
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
        this.ruleIndex = PaxoParser.RULE_expression;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	argumentList() {
	    return this.getTypedRuleContext(ArgumentListContext,0);
	};

	INT_LITERAL() {
	    return this.getToken(PaxoParser.INT_LITERAL, 0);
	};

	UINT_LITERAL() {
	    return this.getToken(PaxoParser.UINT_LITERAL, 0);
	};

	FLOAT_LITERAL() {
	    return this.getToken(PaxoParser.FLOAT_LITERAL, 0);
	};

	DECIMAL_LITERAL() {
	    return this.getToken(PaxoParser.DECIMAL_LITERAL, 0);
	};

	COMPLEX_FLT_LITERAL() {
	    return this.getToken(PaxoParser.COMPLEX_FLT_LITERAL, 0);
	};

	COMPLEX_DEC_LITERAL() {
	    return this.getToken(PaxoParser.COMPLEX_DEC_LITERAL, 0);
	};

	CHAR_LITERAL() {
	    return this.getToken(PaxoParser.CHAR_LITERAL, 0);
	};

	STRING_LITERAL() {
	    return this.getToken(PaxoParser.STRING_LITERAL, 0);
	};

	EMSTRING_LITERAL() {
	    return this.getToken(PaxoParser.EMSTRING_LITERAL, 0);
	};

	BOOLEAN() {
	    return this.getToken(PaxoParser.BOOLEAN, 0);
	};

	VECTOR2D() {
	    return this.getToken(PaxoParser.VECTOR2D, 0);
	};

	VECTOR4D() {
	    return this.getToken(PaxoParser.VECTOR4D, 0);
	};

	NANOTIME_LITERAL() {
	    return this.getToken(PaxoParser.NANOTIME_LITERAL, 0);
	};

	SLICE_LITERAL() {
	    return this.getToken(PaxoParser.SLICE_LITERAL, 0);
	};

	POINTER_LITERAL() {
	    return this.getToken(PaxoParser.POINTER_LITERAL, 0);
	};

	arrayLiteral() {
	    return this.getTypedRuleContext(ArrayLiteralContext,0);
	};

	arrayAccess() {
	    return this.getTypedRuleContext(ArrayAccessContext,0);
	};

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
	    if(listener instanceof PaxoListener ) {
	        listener.enterExpression(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_arrayLiteral;
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
	    if(listener instanceof PaxoListener ) {
	        listener.enterArrayLiteral(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_arrayAccess;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterArrayAccess(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitArrayAccess(this);
		}
	}


}




PaxoParser.ProgramContext = ProgramContext; 
PaxoParser.StatementContext = StatementContext; 
PaxoParser.VarDeclarationContext = VarDeclarationContext; 
PaxoParser.TypeContext = TypeContext; 
PaxoParser.AssignmentContext = AssignmentContext; 
PaxoParser.IfElseStatementContext = IfElseStatementContext; 
PaxoParser.MatchStatementContext = MatchStatementContext; 
PaxoParser.MatchCaseContext = MatchCaseContext; 
PaxoParser.LoopStatementContext = LoopStatementContext; 
PaxoParser.TryCatchStatementContext = TryCatchStatementContext; 
PaxoParser.FunctionDeclarationContext = FunctionDeclarationContext; 
PaxoParser.PkgDeclarationContext = PkgDeclarationContext; 
PaxoParser.BlockContext = BlockContext; 
PaxoParser.ParameterListContext = ParameterListContext; 
PaxoParser.ArgumentListContext = ArgumentListContext; 
PaxoParser.ExpressionContext = ExpressionContext; 
PaxoParser.ArrayLiteralContext = ArrayLiteralContext; 
PaxoParser.ArrayAccessContext = ArrayAccessContext; 
