#include "ofApp.h"
#include <dirent.h>

//--------------------------------------------------------------
void ofApp::setup(){
	b_CameraAlive = false;
	i_CameraAliveCount=0;
	ofSetWindowPosition(100,100);

	/*config = (RASPIVID_CONFIG*)malloc(sizeof(RASPIVID_CONFIG));
	config->width=320;
	config->height=320;
	config->bitrate=0;	// zero: leave as default
	config->framerate=0;
	config->monochrome=0;
	capture = (RaspiCamCvCapture *) raspiCamCvCreateCameraCapture2(0, config);
	free(config);*/


	cout << "TEST" << endl;
	vidGrabber.setDeviceID(0);
	cout << "TEST" << endl;
	vidGrabber.setDesiredFrameRate(60);
	cout << "TEST" << endl;
	vidGrabber.initGrabber(camWidthOri,camHeightOri);
	cout << "TEST" << endl;
	bLearnBakground=true;
	cout << "TEST" << endl;
	
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	cout << "TEST" << endl;
	for(int i = 0; i < devices.size(); i++){
		if(devices[i].bAvailable){
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}else{
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}


	ofSetVerticalSync(true);
	cout << "TEST1" << endl;
	ofSetCircleResolution(80);
	cout << "TEST2" << endl;
	
	ofBackground(54, 54, 54);
	cout << "TEST3" << endl;
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	//soundStream.listDevices();
	
	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	cout << "TEST4" << endl;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
        smoothedVolL     = 0.0;
        smoothedVolR     = 0.0;
	scaledVol		= 0.0;
	//soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

	cout << "TEST5" << endl;
    
    int bufferSize2		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 1.0f;
    bNoise 				= false;
	cout << "TEST6" << endl;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
    //soundStream.listDevices();
	cout << "TEST7" << endl;
    
    //if you want to set the device id to be different than the default
    //soundStream.setDeviceID(1); 	//note some devices are input only and some are output only
    //soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    ofSetFrameRate(30);
    //audio In setup
    
    
    bNeko=true;
	cout << "TEST8" << endl;
    
    DIR* dp=opendir("../../../data/");
    sound_num=0;
    char exts[]=".wav";
    int *l2;
    if (dp!=NULL)
    {
        struct dirent* dent;
        do{
            dent = readdir(dp);
            if (dent!=NULL){
                //l2=(int *)&(dent->d_name);
                //if(*l2 == *(int *)&exts[0]){
                if(strstr(dent->d_name,exts)!=NULL){
                    sound_num++;
                    cout<<dent->d_name<<endl;
                    cout<<sound_num<<endl;
                    ofSoundPlayer SoundBuf;
                    SoundBuf.load(dent->d_name);
                    SoundBuf.setLoop(false);
                    Sounds.push_back(SoundBuf);
                    
                    vector<ofSoundPlayer> SoundBufLoop;
                    for(int i = 0;i<SOUND_LOOP;i++){
                        SoundBufLoop.push_back(SoundBuf);
                    }
                    SoundsLoop.push_back(SoundBufLoop);
                    SoundNames.push_back(dent->d_name);
                }
            }
        }while(dent!=NULL);
        closedir(dp);
    }//フォルダ内のデータを全読み込み
	cout << "TEST9" << endl;

    {
        ofSoundPlayer SoundBuf1;
        SoundBuf1.load("./1/s01.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
        SoundBuf1.load("./1/s02.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
        SoundBuf1.load("./1/s03.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
        SoundBuf1.load("./1/s04.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
        SoundBuf1.load("./1/s05.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
        SoundBuf1.load("./1/s06.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
        SoundBuf1.load("./1/s07.wav");
        SoundBuf1.setLoop(false);
        Sounds1.push_back(SoundBuf1);
    }
	cout << "TEST10" << endl;
    
    //kenpoku
    DivWidth = camWidth/DIV_NUM;
    DivHeight = camHeight/DIV_NUM;
    
    sound_id=0;
    
    //receiver.setup(PORT);
    
    bRenzoku=false;
    bMulti=true;
    blimit=true;
    
    sender.setup(HOST, PORT);
    //GUI
    //gui.setup();
    
	/*gui.add(paradiflevel.setup("Dif Gain", 2.377,0.1,10));
    gui.add(paralevel.setup("HistoryGraph Gain", 1.0,0.1,10));
    gui.add(parameshlevel.setup("MeshData Gain", 1.0,0.1,10));
    gui.add(parasoundthr.setup("Sound Thr", 60,1,255));
    gui.add(parasoundcount.setup("Sound Time Count", 20,5,100));
    gui.add(parasendvalue.setup("Send Value Gain", 1,0.01,100));
    */
	cout << "TEST" << endl;
	paradiflevel= 2.377;
    paralevel=1.0;
    parameshlevel=1.0;
    parasoundthr=10;
    parasoundcount=0;
    parasendvalue=1;
    
    bHideGui=true;
    bkill=false;
    
    idOSC=0;
    bOSCmode=true;
    bdebug=false;
	cout << "TEST11" << endl;
	//cvNamedWindow("RaspiCamTest", 1);
        //それぞれの映像情報の大きさを指定してあげます。
        colorImgOri.allocate(camWidthOri, camHeightOri);
        colorImg.allocate(camWidth, camHeight);
        colorImgHSV.allocate(camWidth, camHeight);
        
        hueImg.allocate(camWidth, camHeight);
        satImg.allocate(camWidth, camHeight);
        briImg.allocate(camWidth, camHeight);
        grayDiff.allocate(camWidth, camHeight);
        grayImagePre.allocate(camWidth, camHeight);
}


//--------------------------------------------------------------
void ofApp::update(){
    //OF_EXIT_APP(0);
    //IplImage* image = raspiCamCvQueryFrame(capture);
	//uchar *pSrc = (uchar*)image->imageData;
	
	//int kes = 0;
	//kes = (int)pSrc[0];
	//cout << "data " << kes << endl;
	//cvShowImage("RaspiCamTest", image);

    vidGrabber.update();
	int i_DetectCount1Fl = 0;
	
    if (vidGrabber.isFrameNew()){
    //if(1){
		//blur(movie, 10);
        
        
        
        colorImgOri.setFromPixels(vidGrabber.getPixels(), camWidthOri,camHeightOri);
		//colorImgOri.setROI(30,80,camWidth,camHeight);
		colorImgOri.setROI(15,40,camWidth,camHeight);
        colorImg.setFromPixels(colorImgOri.getRoiPixels(), camWidth,camHeight);
        //colorImg.setFromPixels(pSrc, camWidth,camHeight);
        
        //HSV
        colorImgHSV = colorImg;
        colorImgHSV.convertRgbToHsv();
        colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
        //unsigned char * colorPixels = colorImg.getPixels();
        
        hueImg.flagImageChanged();
        satImg.flagImageChanged();
        briImg.flagImageChanged();
        //ピクセルの配列をそれぞれに作成
        unsigned char * huePixels = hueImg.getPixels();
        unsigned char * satPixels = satImg.getPixels();
        unsigned char * briPixels = briImg.getPixels();
        
        for(int i=0;i<camWidth*camHeight;i++){
            satPixels[i] = (char)(((int)satPixels[i]* (int)briPixels[i]) >> 8);
        }
        test=(((int)satPixels[0]* (int)briPixels[0]) >> 8);
        //grayImage = satImg;
        if (bLearnBakground == true){
            grayBg = satImg;     // the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }
        
        
        //grayDiff.absDiff(grayImagePre, grayImage);
        unsigned char * DiffPixels = grayDiff.getPixels();
        
        {//差分を絶対値でなく消えるときのみ
        unsigned char * GrayPixels = satImg.getPixels();
        unsigned char * GrayPixelsPre = grayImagePre.getPixels();
        for(int i=0;i<camWidth*camHeight;i++){
            DiffPixels[i]=(unsigned char)(MAX(0,GrayPixelsPre[i]-GrayPixels[i]));
            //if((int)(GrayPixelsPre[i]) > (int)(GrayPixels[i])){
			//	DiffPixels[i]=(unsigned char)(GrayPixelsPre[i]-GrayPixels[i]);
			//}
        }
		float f_score = 0;
		f_score = MAX(0,f_SumGrayImagePre - f_SumGrayImage);
		//cout << "Score " << f_score << endl;
		f_SumGrayImagePre = f_SumGrayImage;

        }
        
        for(int i=0;i<camWidth*camHeight;i++){
            DiffPixels[i]=MIN(255,MAX(0,DiffPixels[i]*paradiflevel));
        }

        //grayDiff.threshold(_th);
        
        if(InitState){
            InitState=false;
            return;
        }
        
        
        grayImagePre=satImg;
        
        colorImgShow = colorImg;
        grayImageShow1=satImg;
        grayImageShow2=grayDiff;
        //grayImageShow3=satImg;
        
        unsigned char * countPixels = grayDiff.getPixels();
        int sum=0;
        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                MeshDataBuf[i][j]=0;
            }
        }
        
        for(int i=0;i<camWidth;i++){
            for(int j=0;j<camHeight;j++){
                MeshDataBuf[(int)floor(i*1.0/DivWidth)][(int)floor(j*1.0/DivHeight)]+=countPixels[i+j*camWidth];
                sum+=countPixels[i+j*camWidth];
            }
        }
		if(sum){
			b_CameraAlive = true;
		}


        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                if(0){//TEST
				MeshDataBuf[i][j]=MeshDataBuf[i][j]*parameshlevel/MESHLEVEL;
                if(MeshData[i][j] <= MeshDataBuf[i][j]){
                    MeshData[i][j] = MeshDataBuf[i][j];
                }else{
                    MeshData[i][j] = (MeshData[i][j]*3+MeshDataBuf[i][j])/4 ;
                }
				}else{
                    MeshData[i][j] = MeshDataBuf[i][j]/100;
				}

                MeshDataGauss[i][j]=0;
            }
        }
        for(int i=G_SIZE_H;i<DIV_NUM-G_SIZE_H;i++){
            for(int j=G_SIZE_H;j<DIV_NUM-G_SIZE_H;j++){
                for(int k=0;k<G_SIZE;k++){
                    for(int l=0;l<G_SIZE;l++){
                        MeshDataGauss[i][j]+=(int)(MeshData[i-G_SIZE_H+k][j-G_SIZE_H+l]*Gauss[k][l]/(1.0*G_SIZE*G_SIZE));
                        //MeshDataGauss[i][j]+=5;
                    }
                }
            }
        }

        for(int i=G_SIZE_H;i<DIV_NUM-G_SIZE_H;i++){
            for(int j=G_SIZE_H;j<DIV_NUM-G_SIZE_H;j++){
				if(MeshDataGauss[i][j] > MeshDataGaussMove[i][j]){
                	MeshDataGaussMoveFilt[i][j]= MeshDataGauss[i][j];
				}else{
                	MeshDataGaussMoveFilt[i][j]= 0;
				}
			}
		}

        for(int i=G_SIZE_MOVE_H;i<DIV_NUM-G_SIZE_MOVE_H;i++){
            for(int j=G_SIZE_MOVE_H;j<DIV_NUM-G_SIZE_MOVE_H;j++){
                MeshDataGaussMove[i][j]=0;
                for(int k=0;k<G_SIZE_MOVE;k++){
                    for(int l=0;l<G_SIZE_MOVE;l++){
                        MeshDataGaussMove[i][j] = MAX(MeshDataGauss[i-G_SIZE_MOVE_H+k][j-G_SIZE_MOVE_H+l],MeshDataGaussMove[i][j]);
                        //MeshDataGauss[i][j]+=5;
                    }
                }
            }
        }

        MaxGauss=0;
        SendValueBuf=0;
        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                if(MeshDataGauss[i][j]>MaxGauss){
                    MaxGauss=MeshDataGauss[i][j];
                }
                MeshDataDetect[i][j] /= 2;
                //if(MeshDataGauss[i][j] > parasoundthr){
                if(MeshDataGaussMoveFilt[i][j] > parasoundthr){
					if((i>2) && (j>2) && (i<(DIV_NUM-3)) && (j<(DIV_NUM-3))){
                    	SoundFlag = true;
                    	SendPosX = i;
                    	SendPosY = j;
                    	SendValueBuf += 1;
                		MeshDataDetect[i][j] = MeshDataGaussMoveFilt[i][j];
						i_DetectCount1Fl++;
					}
                }
            }
        }
        
        SumDiff=sum*paralevel;
        volHistory.push_back(SumDiff/1000000.0);
        //if we are bigger the the size we want to record - lets drop the oldest value
        if( volHistory.size() >= 400 ){
            volHistory.erase(volHistory.begin(), volHistory.begin()+1);
        }
    }

    
    SoundCount++;
    SoundCount=MIN(SoundCount,(int)parasoundcount);
	


    if(SoundFlag){
        SoundFlag=false;
		if(i_DetectCount1Fl < (DIV_NUM*DIV_NUM/100)){
        if (SoundCount>=parasoundcount) {
            SendTotal+=1;
            SendValue=SendValueBuf;
			SoundCount=0;
            ofxOscMessage m;
            m.setAddress("/soundpos");
            m.addIntArg(SendPosX);
            m.addIntArg(SendPosY);
            m.addIntArg(MIN((int)(SendValue*parasendvalue),100));
            m.addIntArg(DIV_NUM);
            sender.sendMessage(m);
			cout << "Detect " << i_DetectCount1Fl<<" time " << SendPosX << ":"<< SendPosY << ":" << SendValue*parasendvalue << endl;
        }
		}else{
			cout << "Detect Error Too Much " << i_DetectCount1Fl<<" time "<< SendPosX << ":"<< SendPosY << ":" << SendValue*parasendvalue << endl;
		}
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(225);
	ofDrawBitmapString("press 's' to unpause the audio\n'e' to pause the audio", 31, 32);
	
	ofNoFill();
	i_CameraAliveCount++;
    cout << "test" << i_CameraAliveCount <<":"<< (int)(b_CameraAlive) << endl;
	if((i_CameraAliveCount > 20) && (b_CameraAlive != true)){
		cout << "camera error" << endl;
		OF_EXIT_APP(0);
	}

    //grayImageShow.draw(0, 0);
    
    colorImgShow.draw(0,0,camWidth, camHeight);
    grayImageShow1.draw(camWidth, 0,camWidth, camHeight);
    grayImageShow2.draw(0, camHeight,camWidth, camHeight);
    //grayImageShow3.draw(camWidth, camHeight,camWidth, camHeight);

    ofPushStyle();
    ofPushMatrix();
    if(1){
        ofFill();
        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                int colorbuf;
                if(bGauss){
                    colorbuf=MIN(255,MeshData[i][j]);
                }else{
                    colorbuf=MIN(255,MeshDataGauss[i][j]);
                    //colorbuf=MIN(255,MeshDataGaussMove[i][j]);
                    //colorbuf=MIN(255,MeshDataGaussMoveFilt[i][j]);
                }ofSetColor(colorbuf, colorbuf, colorbuf);
                ofRect(camWidth+i*DivWidth, camHeight+j*DivHeight, DivWidth, DivHeight);
            }
        }
        ofNoFill();
    }
    if(1){
        ofFill();
        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                int colorbuf;
                if(bGauss){
                    colorbuf=MIN(255,MeshData[i][j]);
                }else{
                    //colorbuf=MIN(255,MeshDataGauss[i][j]);
                    colorbuf=MIN(255,MeshDataGaussMove[i][j]);
                    //colorbuf=MIN(255,MeshDataGaussMoveFilt[i][j]);
                }ofSetColor(colorbuf, colorbuf, colorbuf);
                ofRect(2*camWidth+i*DivWidth, j*DivHeight, DivWidth, DivHeight);
            }
        }
        ofNoFill();
    }

    if(1){
        ofFill();
        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                int colorbuf;
                if(bGauss){
                    colorbuf=MIN(255,MeshData[i][j]);
                }else{
                    //colorbuf=MIN(255,MeshDataGauss[i][j]);
                    //colorbuf=MIN(255,MeshDataGaussMove[i][j]);
                    colorbuf=MIN(255,MeshDataGaussMoveFilt[i][j]);
                }ofSetColor(colorbuf, colorbuf, colorbuf);
                ofRect(2*camWidth+i*DivWidth, camHeight+j*DivHeight, DivWidth, DivHeight);
            }
        }
        ofNoFill();
    }
    
	if(1){
        ofFill();
        for(int i=0;i<DIV_NUM;i++){
            for(int j=0;j<DIV_NUM;j++){
                int colorbuf;
                if(bGauss){
                    colorbuf=MIN(255,MeshData[i][j]);
                }else{
                    //colorbuf=MIN(255,MeshDataGauss[i][j]);
                    //colorbuf=MIN(255,MeshDataGaussMove[i][j]);
                    //colorbuf=MIN(255,MeshDataGaussMoveFilt[i][j]);
                    colorbuf=MIN(255,MeshDataDetect[i][j]);
                }ofSetColor(colorbuf, colorbuf, colorbuf);
                ofRect(3*camWidth+i*DivWidth, camHeight+j*DivHeight, DivWidth, DivHeight);
            }
        }
        ofNoFill();
    }


    ofPopMatrix();
    ofPopStyle();
    
    
    // draw the average volume:
    ofPushStyle();
    ofPushMatrix();
    //ofTranslate(765, 170, 0);
    ofTranslate(1265, 170, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
    ofRect(0, 0, 400, 400);
    
    ofSetColor(245, 58, 135);
    ofFill();
    ofCircle(200, 200, scaledVol * 190.0f);
    
    //lets draw the volume history as a graph
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, 400);
        
        ofVertex(i, 400 - volHistory[i] * 10);
        
        if( i == volHistory.size() -1 ) ofVertex(i, 400);
    }
    ofEndShape(false);		
    
    ofPopMatrix();
    ofPopStyle();
    
    
    
    
	ofSetColor(225);
    string reportString = "";
    if(bkill){
        reportString+=("\nkill this app");
    }
    if(bdebug){
        reportString+=("\nDebugMode");
        reportString+=("\n");
        reportString+=ofToString(sound_num);
        reportString+=("\nSoundId:");
        reportString+=ofToString(idOSC);
        reportString+=SoundNames[idOSC];
        reportString+=("\nSoundId:");
        reportString+=ofToString(SumDiff);
        reportString+=("\nStest:");
        reportString+=ofToString(test);
        reportString+=("\nMeshData:");
        reportString+=ofToString(MeshData[0][0]);
        reportString+=("\nCountData:");
        reportString+=ofToString(SoundCount);
        reportString+=("\nMaxGaussValue:");
        reportString+=ofToString(MaxGauss);
        reportString+=("\nSendTotal:");
        reportString+=ofToString(SendTotal);
        reportString+=(" X:");
        reportString+=ofToString(SendPosX);
        reportString+=(" Y:");
        reportString+=ofToString(SendPosY);
        reportString+=(" Value:");
        reportString+=ofToString((int)(SendValue*parasendvalue));
    }
    ofDrawBitmapString(reportString, 432, 459);
    

    //if(bHideGui) gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){	
	
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    /*if(SoundFlag){
        SoundFlag=false;
        if (SoundCount>=parasoundcount) {
            SendTotal+=1;
            SendValue=SendValueBuf;
            Sounds[idOSC].setMultiPlay(true);
            Sounds[idOSC].setVolume(1.0);
            Sounds[idOSC].setSpeed(1.0);
            Sounds[idOSC].play();
            if(bSoundRand){
                int idOSCBuf;
                idOSCBuf=idOSC;
                while (true) {
                    idOSC=MIN(sound_num-1,(int)floor(ofRandom(1.0)*sound_num));
                    if(idOSC!=idOSCBuf){
                        break;
                    }
                }
            }SoundCount=0;
            ofxOscMessage m;
            m.setAddress("/soundpos");
            m.addIntArg(SendPosX);
            m.addIntArg(SendPosY);
            m.addIntArg(MIN((int)(SendValue*parasendvalue),100));
            m.addIntArg(DIV_NUM);
            sender.sendMessage(m);
        }
    }*/
}


void ofApp::playscene(int i){
    Sounds1[i].setMultiPlay(true);
    Sounds1[i].setVolume(1.0);
    Sounds1[i].setSpeed(1.0);
    Sounds1[i].play();
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	//if( key == 's' ){
	//	soundStream.start();
	//}
	//if( key == 'e' ){
	//	soundStream.stop();
	//}
    if (key=='1') {
        playscene(0);
    }
    if (key=='2') {
        playscene(1);
    }
    if (key=='3') {
        playscene(2);
    }
    if (key=='4') {
        playscene(3);
    }
    if (key=='5') {
        playscene(4);
    }
    if (key=='6') {
        playscene(5);
    }
    if (key=='7') {
        playscene(6);
    }
    
    if(key == 'b') bLearnBakground = true;

    if( key == OF_KEY_RETURN){
        SoundFlag=true;
        SendPosX = (int)(ofRandom(1.0)*DIV_NUM);
        SendPosY = (int)(ofRandom(1.0)*DIV_NUM);
    }
    
    if( key == OF_KEY_UP){
        if(idOSC<(MAX_OSC_NUM-1)){
            idOSC++;
        }
    }
    if( key == OF_KEY_DOWN){
        if(idOSC>0){
            idOSC--;
        }
    }
    
    if(bdebug){
    if( key == 'l'){
        blimit=!blimit;
    }
    if( key == 'r'){
        //bRenzoku=!bRenzoku;
        bSoundRand=!bSoundRand;
    }
    if(key == 'm'){
        bMulti=!bMulti;
    }
    if( key == 'c' ){
        bNeko= !bNeko;
    }
    if( key == 'o'){
        bOSCmode=!bOSCmode;
    }
    }
    
    if(key == 'h') {
        bHideGui = !bHideGui;
    }
    if(key == 'g') {
        bGauss = !bGauss;
    }
    if(key == 'd'){
        bdebug = !bdebug;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
    float height = (float)ofGetHeight();
    float heightPct = ((height-y) / height);
    targetFrequency = 2000.0f * heightPct;
    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
}

void ofApp::changeSound(){
}

