* C- compiler version
* File compiled:  ./hw7demo/array.tm
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:     LD  3,-1(1)	Load return address 
 10:     LD  1,0(1)	Adjust fp 
 11:    JMP  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)	Store return address 
 13:    INB  2,2,2	Grab bool input 
 14:     LD  3,-1(1)	Load return address 
 15:     LD  1,0(1)	Adjust fp 
 16:    JMP  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)	Store return address 
 18:     LD  3,-2(1)	Load parameter 
 19:   OUTB  3,3,3	Output bool 
 20:     LD  3,-1(1)	Load return address 
 21:     LD  1,0(1)	Adjust fp 
 22:    JMP  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)	Store return address 
 24:    INC  2,2,2	Grab char input 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load parameter 
 30:   OUTC  3,3,3	Output char 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION get
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF:  -4
* CALL EXPRESSION
* CALL output
 40:     ST  1,-4(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -5
* TOFF: -6
* OP EXPRESSION
 41:     LD  3,-2(1)	2 Load address of base of array 583 x
 42:     ST  3,-6(1)	Push left side 
* TOFF: -7
 43:    LDC  3,0(6)	Load Integer constant 
* TOFF: -6
 44:     LD  4,-6(1)	1 Pop left into ac1 
 45:    SUB  3,4,3	1 Compute location from index 
 46:     LD  3,0(3)	1 Load array element 
 47:     ST  3,-6(1)	Push parameter 1001 
* Param end output
 48:    LDA  1,-4(1)	1 Ghost frame becomes new active frame 
 49:    LDA  3,1(7)	Return address in ac 
 50:    JMP  7,-45(7)	CALL OUTPUT output
 51:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -4
* CALL EXPRESSION
* CALL outnl
 52:     ST  1,-4(1)	3 Store fp in ghost frame for outnl
* Param end outnl
 53:    LDA  1,-4(1)	Ghost frame becomes new active frame 
 54:    LDA  3,1(7)	Return address in ac 
 55:    JMP  7,-22(7)	CALL OUTPUT outnl
 56:    LDA  3,0(2)	Save the result in ac 
* CALL end outnl
* TOFF: -4
* ASSIGNMENT EXPRESSION
 57:    LDC  3,1(6)	Load Integer constant 
 58:     ST  3,-4(1)	Push index 373 
* TOFF: -5
 59:    LDC  3,666(6)	Load Integer constant 
* TOFF: -4
 60:     LD  4,-4(1)	Pop index 
 61:    LDA  5,-2(1)	Load address of base of array 390 x
 62:    SUB  5,5,4	Compute offset of value 
 63:     ST  3,0(5)	Store variable x
* RETURN
* OP EXPRESSION
 64:     LD  3,-2(1)	2 Load address of base of array 583 x
 65:     ST  3,-4(1)	Push left side 
* TOFF: -5
 66:     LD  3,-3(1)	1 load variable 861 i
* TOFF: -4
 67:     LD  4,-4(1)	1 Pop left into ac1 
 68:    SUB  3,4,3	1 Compute location from index 
 69:     LD  3,0(3)	1 Load array element 
 70:    LDA  2,0(3)	Copy result to ret register 
 71:     LD  3,-1(1)	Load return address 
 72:     LD  1,0(1)	Adjust fp 
 73:    JMP  7,0(3)	Return 
* Compound Body
* TOFF:  -2
* END COMPOUND
* Add standard closing in case there is no return statement
 74:    LDC  2,0(6)	Set return value to 0 
 75:     LD  3,-1(1)	Load return address 
 76:     LD  1,0(1)	Adjust fp 
 77:    JMP  7,0(3)	Return 
* END FUNCTION get
* TOFF: -2
* FUNCTION main
 78:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF:  -9
 79:    LDC  3,5(6)	load array size 124 x
 80:     ST  3,-2(1)	save array size x
* ASSIGNMENT EXPRESSION
 81:    LDC  3,2(6)	Load Integer constant 
 82:     ST  3,-8(1)	Store variable dog
* ASSIGNMENT EXPRESSION
 83:    LDC  3,0(6)	Load Integer constant 
 84:     ST  3,-9(1)	Push index 373 
* TOFF: -10
 85:    LDC  3,3(6)	Load Integer constant 
* TOFF: -9
 86:     LD  4,-9(1)	Pop index 
 87:    LDA  5,-3(1)	Load address of base of array 390 x
 88:    SUB  5,5,4	Compute offset of value 
 89:     ST  3,0(5)	Store variable x
* CALL EXPRESSION
* CALL output
 90:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
 91:    LDC  3,0(6)	Load Integer constant 
* TOFF: -11
 92:    LDA  5,-3(1)	3 Load address of base of array 626 x
 93:    SUB  5,5,3	2 Compute location from index 
 94:     LD  3,0(5)	2 Load array element 
 95:     ST  3,-11(1)	Push parameter 1001 
* Param end output
 96:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
 97:    LDA  3,1(7)	Return address in ac 
 98:    JMP  7,-93(7)	CALL OUTPUT output
 99:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* ASSIGNMENT EXPRESSION
100:    LDC  3,1(6)	Load Integer constant 
101:     ST  3,-9(1)	Push index 373 
* TOFF: -10
* OP EXPRESSION
* TOFF: -11
102:    LDC  3,0(6)	Load Integer constant 
* TOFF: -10
103:    LDA  5,-3(1)	3 Load address of base of array 626 x
104:    SUB  5,5,3	2 Compute location from index 
105:     LD  3,0(5)	2 Load array element 
* TOFF: -9
106:     LD  4,-9(1)	Pop index 
107:     LD  5,-3(1)	Load address of base of array 493 x
108:    SUB  5,5,4	Compute offset of value 
109:     ST  3,0(5)	Store variable x
* CALL EXPRESSION
* CALL output
110:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
111:    LDC  3,1(6)	Load Integer constant 
* TOFF: -11
112:    LDA  5,-3(1)	3 Load address of base of array 626 x
113:    SUB  5,5,3	2 Compute location from index 
114:     LD  3,0(5)	2 Load array element 
115:     ST  3,-11(1)	Push parameter 1001 
* Param end output
116:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
117:    LDA  3,1(7)	Return address in ac 
118:    JMP  7,-113(7)	CALL OUTPUT output
119:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* ASSIGNMENT EXPRESSION
120:    LDC  3,2(6)	Load Integer constant 
121:     ST  3,-9(1)	Push index 373 
* TOFF: -10
* OP EXPRESSION
* OP EXPRESSION
* TOFF: -11
122:    LDC  3,1(6)	Load Integer constant 
* TOFF: -10
123:    LDA  5,-3(1)	3 Load address of base of array 626 x
124:    SUB  5,5,3	2 Compute location from index 
125:     LD  3,0(5)	2 Load array element 
126:     ST  3,-10(1)	Push the left side 677 
* TOFF: -11
127:    LDC  3,1(6)	Load Integer constant 
* TOFF: -10
128:     LD  4,-10(1)	Load Left into 1 +
129:    ADD  3,4,3	Op + +
* TOFF: -9
130:     LD  4,-9(1)	Pop index 
131:     LD  5,-3(1)	Load address of base of array 493 x
132:    SUB  5,5,4	Compute offset of value 
133:     ST  3,0(5)	Store variable x
* CALL EXPRESSION
* CALL output
134:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
135:    LDC  3,2(6)	Load Integer constant 
* TOFF: -11
136:    LDA  5,-3(1)	3 Load address of base of array 626 x
137:    SUB  5,5,3	2 Compute location from index 
138:     LD  3,0(5)	2 Load array element 
139:     ST  3,-11(1)	Push parameter 1001 
* Param end output
140:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
141:    LDA  3,1(7)	Return address in ac 
142:    JMP  7,-137(7)	CALL OUTPUT output
143:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* ASSIGNMENT EXPRESSION
* OP EXPRESSION
144:     LD  3,-8(1)	2 Load variable 815 dog
145:     ST  3,-9(1)	Push the left side 677 
* TOFF: -10
146:     LD  3,-8(1)	2 Load variable 815 dog
* TOFF: -9
147:     LD  4,-9(1)	Load Left into 1 +
148:    ADD  3,4,3	Op + +
149:     ST  3,-9(1)	Push index 373 
* TOFF: -10
150:    LDC  3,496(6)	Load Integer constant 
* TOFF: -9
151:     LD  4,-9(1)	Pop index 
152:    LDA  5,-3(1)	Load address of base of array 390 x
153:    SUB  5,5,4	Compute offset of value 
154:     ST  3,0(5)	Store variable x
* CALL EXPRESSION
* CALL output
155:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
156:    LDC  3,4(6)	Load Integer constant 
* TOFF: -11
157:    LDA  5,-3(1)	3 Load address of base of array 626 x
158:    SUB  5,5,3	2 Compute location from index 
159:     LD  3,0(5)	2 Load array element 
160:     ST  3,-11(1)	Push parameter 1001 
* Param end output
161:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
162:    LDA  3,1(7)	Return address in ac 
163:    JMP  7,-158(7)	CALL OUTPUT output
164:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* CALL EXPRESSION
* CALL outnl
165:     ST  1,-9(1)	3 Store fp in ghost frame for outnl
* Param end outnl
166:    LDA  1,-9(1)	Ghost frame becomes new active frame 
167:    LDA  3,1(7)	Return address in ac 
168:    JMP  7,-135(7)	CALL OUTPUT outnl
169:    LDA  3,0(2)	Save the result in ac 
* CALL end outnl
* TOFF: -9
* ASSIGNMENT EXPRESSION
170:    LDC  3,2(6)	Load Integer constant 
171:     ST  3,-8(1)	Store variable dog
* ASSIGNMENT EXPRESSION
172:    LDC  3,0(6)	Load Integer constant 
173:     ST  3,-9(1)	Push index 373 
* TOFF: -10
174:    LDC  3,3(6)	Load Integer constant 
* TOFF: -9
175:     LD  4,-9(1)	Pop index 
176:    LDA  5,-1(0)	Load address of base of array 383 y
177:    SUB  5,5,4	Compute offset of value 
178:     ST  3,0(5)	Store variable y
* CALL EXPRESSION
* CALL output
179:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
180:    LDC  3,0(6)	Load Integer constant 
* TOFF: -11
181:    LDA  5,-1(0)	1 Load address of base of array 620 y
182:    SUB  5,5,3	2 Compute location from index 
183:     LD  3,0(5)	2 Load array element 
184:     ST  3,-11(1)	Push parameter 1001 
* Param end output
185:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
186:    LDA  3,1(7)	Return address in ac 
187:    JMP  7,-182(7)	CALL OUTPUT output
188:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* ASSIGNMENT EXPRESSION
189:    LDC  3,1(6)	Load Integer constant 
190:     ST  3,-9(1)	Push index 373 
* TOFF: -10
* OP EXPRESSION
* TOFF: -11
191:    LDC  3,0(6)	Load Integer constant 
* TOFF: -10
192:    LDA  5,-1(0)	1 Load address of base of array 620 y
193:    SUB  5,5,3	2 Compute location from index 
194:     LD  3,0(5)	2 Load array element 
* TOFF: -9
195:     LD  4,-9(1)	Pop index 
196:    LDA  5,-1(0)	Load address of base of array 383 y
197:    SUB  5,5,4	Compute offset of value 
198:     ST  3,0(5)	Store variable y
* CALL EXPRESSION
* CALL output
199:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
200:    LDC  3,1(6)	Load Integer constant 
* TOFF: -11
201:    LDA  5,-1(0)	1 Load address of base of array 620 y
202:    SUB  5,5,3	2 Compute location from index 
203:     LD  3,0(5)	2 Load array element 
204:     ST  3,-11(1)	Push parameter 1001 
* Param end output
205:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
206:    LDA  3,1(7)	Return address in ac 
207:    JMP  7,-202(7)	CALL OUTPUT output
208:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* ASSIGNMENT EXPRESSION
209:    LDC  3,2(6)	Load Integer constant 
210:     ST  3,-9(1)	Push index 373 
* TOFF: -10
* OP EXPRESSION
* OP EXPRESSION
* TOFF: -11
211:    LDC  3,1(6)	Load Integer constant 
* TOFF: -10
212:    LDA  5,-1(0)	1 Load address of base of array 620 y
213:    SUB  5,5,3	2 Compute location from index 
214:     LD  3,0(5)	2 Load array element 
215:     ST  3,-10(1)	Push the left side 677 
* TOFF: -11
216:    LDC  3,311(6)	Load Integer constant 
* TOFF: -10
217:     LD  4,-10(1)	Load Left into 1 +
218:    ADD  3,4,3	Op + +
* TOFF: -9
219:     LD  4,-9(1)	Pop index 
220:    LDA  5,-1(0)	Load address of base of array 383 y
221:    SUB  5,5,4	Compute offset of value 
222:     ST  3,0(5)	Store variable y
* CALL EXPRESSION
* CALL output
223:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
224:    LDC  3,2(6)	Load Integer constant 
* TOFF: -11
225:    LDA  5,-1(0)	1 Load address of base of array 620 y
226:    SUB  5,5,3	2 Compute location from index 
227:     LD  3,0(5)	2 Load array element 
228:     ST  3,-11(1)	Push parameter 1001 
* Param end output
229:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
230:    LDA  3,1(7)	Return address in ac 
231:    JMP  7,-226(7)	CALL OUTPUT output
232:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* ASSIGNMENT EXPRESSION
* OP EXPRESSION
233:     LD  3,-8(1)	2 Load variable 815 dog
234:     ST  3,-9(1)	Push the left side 677 
* TOFF: -10
235:     LD  3,-8(1)	2 Load variable 815 dog
* TOFF: -9
236:     LD  4,-9(1)	Load Left into 1 +
237:    ADD  3,4,3	Op + +
238:     ST  3,-9(1)	Push index 373 
* TOFF: -10
239:    LDC  3,496(6)	Load Integer constant 
* TOFF: -9
240:     LD  4,-9(1)	Pop index 
241:    LDA  5,-1(0)	Load address of base of array 383 y
242:    SUB  5,5,4	Compute offset of value 
243:     ST  3,0(5)	Store variable y
* CALL EXPRESSION
* CALL output
244:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
245:    LDC  3,4(6)	Load Integer constant 
* TOFF: -11
246:    LDA  5,-1(0)	1 Load address of base of array 620 y
247:    SUB  5,5,3	2 Compute location from index 
248:     LD  3,0(5)	2 Load array element 
249:     ST  3,-11(1)	Push parameter 1001 
* Param end output
250:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
251:    LDA  3,1(7)	Return address in ac 
252:    JMP  7,-247(7)	CALL OUTPUT output
253:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* CALL EXPRESSION
* CALL outnl
254:     ST  1,-9(1)	3 Store fp in ghost frame for outnl
* Param end outnl
255:    LDA  1,-9(1)	Ghost frame becomes new active frame 
256:    LDA  3,1(7)	Return address in ac 
257:    JMP  7,-224(7)	CALL OUTPUT outnl
258:    LDA  3,0(2)	Save the result in ac 
* CALL end outnl
* TOFF: -9
* ASSIGNMENT EXPRESSION
* CALL EXPRESSION
* CALL get
* TOFF: -9
259:     ST  1,-9(1)	2 Store fp in ghost frame for get
* TOFF: -10
* TOFF: -11
* 1071 Param 1
260:    LDA  3,-1(0)	Load address of base of array 1025 y
261:     ST  3,-11(1)	1101 Push parameter 
* TOFF: -12
* 1071 Param 2
262:    LDC  3,2065790368(6)	Load integer constant 
263:     ST  3,-12(1)	3 Push parameter 
* TOFF: -13
* 1071 Param 3
264:     ST  3,-13(1)	3 Push parameter 
* Param end get
265:    LDA  1,-9(1)	Ghost frame becomes new active frame 
266:    LDA  3,1(7)	Return address in ac 
267:    JMP  7,-229(7)	CALL OUTPUT get
268:    LDA  3,0(2)	Save the result in ac 
* CALL end get
* TOFF: -9
269:     ST  3,-8(1)	Store variable dog
* CALL EXPRESSION
* CALL output
270:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
271:     LD  3,-8(1)	2 Load variable 815 dog
272:     ST  3,-11(1)	Push parameter 1001 
* Param end output
273:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
274:    LDA  3,1(7)	Return address in ac 
275:    JMP  7,-270(7)	CALL OUTPUT output
276:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* CALL EXPRESSION
* CALL output
277:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* CALL EXPRESSION
* CALL get
* TOFF: -11
278:     ST  1,-11(1)	2 Store fp in ghost frame for get
* TOFF: -12
* TOFF: -13
* 1071 Param 1
279:    LDA  3,-1(0)	Load address of base of array 1025 y
280:     ST  3,-13(1)	1101 Push parameter 
* TOFF: -14
* 1071 Param 2
281:    LDC  3,2065790368(6)	Load integer constant 
282:     ST  3,-14(1)	3 Push parameter 
* TOFF: -15
* 1071 Param 3
283:     ST  3,-15(1)	3 Push parameter 
* Param end get
284:    LDA  1,-11(1)	Ghost frame becomes new active frame 
285:    LDA  3,1(7)	Return address in ac 
286:    JMP  7,-248(7)	CALL OUTPUT get
287:    LDA  3,0(2)	Save the result in ac 
* CALL end get
* TOFF: -11
288:     ST  3,-11(1)	Push parameter 1001 
* Param end output
289:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
290:    LDA  3,1(7)	Return address in ac 
291:    JMP  7,-286(7)	CALL OUTPUT output
292:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* CALL EXPRESSION
* CALL output
293:     ST  1,-9(1)	1 Store fp in ghost frame for output
* Param 1
* TOFF: -10
* TOFF: -11
* OP EXPRESSION
* TOFF: -12
294:    LDC  3,1(6)	Load Integer constant 
* TOFF: -11
295:    LDA  5,-3(1)	3 Load address of base of array 626 x
296:    SUB  5,5,3	2 Compute location from index 
297:     LD  3,0(5)	2 Load array element 
298:     ST  3,-11(1)	Push parameter 1001 
* Param end output
299:    LDA  1,-9(1)	1 Ghost frame becomes new active frame 
300:    LDA  3,1(7)	Return address in ac 
301:    JMP  7,-296(7)	CALL OUTPUT output
302:    LDA  3,0(2)	Save the result in ac 
* CALL end output
* TOFF: -9
* CALL EXPRESSION
* CALL outnl
303:     ST  1,-9(1)	3 Store fp in ghost frame for outnl
* Param end outnl
304:    LDA  1,-9(1)	Ghost frame becomes new active frame 
305:    LDA  3,1(7)	Return address in ac 
306:    JMP  7,-273(7)	CALL OUTPUT outnl
307:    LDA  3,0(2)	Save the result in ac 
* CALL end outnl
* TOFF: -9
* Compound Body
* TOFF:  -2
* END COMPOUND
* Add standard closing in case there is no return statement
308:    LDC  2,0(6)	Set return value to 0 
309:     LD  3,-1(1)	Load return address 
310:     LD  1,0(1)	Adjust fp 
311:    JMP  7,0(3)	Return 
* END FUNCTION main
* TOFF: -2
  0:    JMP  7,311(7)	Jump to init [backpatch] 
* INIT
312:    LDA  1,-6(0)	set first frame at end of globals 
313:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
314:    LDC  3,5(6)	load size of array y
315:     ST  3,0(0)	save size of array y
* END INIT GLOBALS AND STATICS
316:    LDA  3,1(7)	Return address in ac 
317:    JMP  7,-240(7)	Jump to main 
318:   HALT  0,0,0	DONE! 
* END INIT
