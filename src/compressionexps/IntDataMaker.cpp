/* Copyright (c) 2005, Regents of Massachusetts Institute of Technology, 
 * Brandeis University, Brown University, and University of Massachusetts 
 * Boston. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright 
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *   - Neither the name of Massachusetts Institute of Technology, 
 *     Brandeis University, Brown University, or University of 
 *     Massachusetts Boston nor the names of its contributors may be used 
 *     to endorse or promote products derived from this software without 
 *     specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 /**
 */
#include "IntDataMaker.h"

IntDataMaker::IntDataMaker() {
}

IntDataMaker::~IntDataMaker() {
}

bool IntDataMaker::run(Globals* g, const vector<string>& args) {
  if(args.size()<1){
    cout << "at least one argument! " <<endl;
    return false;
  }
  _file = args[0].c_str();

  cout << "IntDataMaker: Making file " << _file << endl;
    	bool success=true;
  
	//string path=DELTAPOS_TEST_BIG;
	ColumnExtracter* ce = new ColumnExtracter(_file, 1, g->force_rebuild);
	IntEncoder* encoder=new IntEncoder((Operator*) ce, 0, 8*PAGE_SIZE);
	IntDecoder* decoder=new IntDecoder(false);
	PagePlacer* pagePlacer=new PagePlacer(encoder, decoder, 1, true);

  int i=0;
  for (; i< 100; i++)
    if (strncmp(_file+i, "dnatest",7) == 0) {
      break;
    }

  char* temp = new char[30];
  sprintf(temp, "test1Int%s", (_file+i+8));
  pagePlacer->placeColumn(temp, false, false);
  sprintf(temp, "mv test1Int%s " RUNTIME_DATA, (_file+i+8));
  system(temp);
  delete pagePlacer;
  delete decoder;

  return success;	
}
