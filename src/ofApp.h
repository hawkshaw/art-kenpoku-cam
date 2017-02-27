#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "RaspiCamCV.h"
//#include "cv.h"
//#include "highgui.h"
//#include "ofxGui.h"

#define HOST "192.168.10.11"
//#define HOST "localhost"

#define PORT 7400
#define NUM_MSG_STRINGS 20
#define SOUND_LOOP 6 //ÂêåÊôÇÂÜçÁîüÂèØËÉΩÂõûÊï∞
#define MAX_OSC_NUM 39


//#define camWidth 1280
//#define camHeight 720

//#define camWidthOri 640
//#define camHeightOri 480
//#define camWidth 400
//#define camHeight 400

#define camWidthOri 320
#define camHeightOri 240
#define camWidth 200
#define camHeight 200



#define DIV_NUM 40
#define MESHLEVEL 100
#define G_SIZE 5//5
#define G_SIZE_H 2//2
#define G_SIZE_MOVE 5//7
#define G_SIZE_MOVE_H 2//3

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
    
    ofVideoGrabber 		vidGrabber;
    ofxCvColorImage			colorImgOri;
    ofxCvColorImage			colorImg;
    ofxCvColorImage			colorImgHSV;

    ofxCvColorImage			colorImgShow;
    ofxCvGrayscaleImage 	grayImageShow1;
    ofxCvGrayscaleImage 	grayImageShow2;
    ofxCvGrayscaleImage 	grayImageShow3;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayImagePre;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;

    ofxCvGrayscaleImage hueImg;
    ofxCvGrayscaleImage satImg;
    ofxCvGrayscaleImage briImg;

    ofxCvGrayscaleImage 	grayImageCount;
    
    //kenpoku
    bool bLearnBakground;
    bool SoundFlag = false;
    int SoundCount;//間を空けるためのカウンタ
    int SumDiff;
    bool InitState = true;
    int test;
    int MeshData[DIV_NUM][DIV_NUM];
    int MeshDataBuf[DIV_NUM][DIV_NUM];
    int MeshDataGauss[DIV_NUM][DIV_NUM];
    int MeshDataGaussMove[DIV_NUM][DIV_NUM];
    int MeshDataGaussMoveFilt[DIV_NUM][DIV_NUM];
    int MeshDataShow[DIV_NUM][DIV_NUM];
    int MeshDataDetect[DIV_NUM][DIV_NUM];
    int Gauss[5][5]={{1,1,1,1,1},
        {1,2,2,2,1},
        {1,2,3,2,1},
        {1,2,2,2,1},
        {1,1,1,1,1}
    };
    bool bGauss = false;
    bool bSoundRand = true;
    
    int DivWidth,DivHeight;
    int SendPosX,SendPosY,SendValue,SendValueBuf;
    int SendTotal = 0;
    
    int MaxGauss;
    
    void playscene(int i);
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void changeSound();
				
		void audioIn(float * input, int bufferSize, int nChannels); 
	
		vector <float> left;
		vector <float> right;
		vector <float> volHistory;
		
		int 	bufferCounter;
		int 	drawCounter;
		
		float smoothedVol;
        float smoothedVolL;
        float smoothedVolR;
        float smoothedVol_1f;
        float smoothedVol_2f;
		float scaledVol;
		
		ofSoundStream soundStream;
    
        //audio output
        void audioOut(float * input, int bufferSize, int nChannels);
        float 	pan;
        int		sampleRate;
        bool 	bNoise;
        float 	volume;
    
        vector <float> lAudio;
        vector <float> rAudio;
    
        //------------------- for the simple sine wave synthesis
        float 	targetFrequency;
        float 	phase;
        float 	phaseAdder;
        float 	phaseAdderTarget;
    
        vector<ofSoundPlayer> Sounds;
        vector<ofSoundPlayer> Sounds1;
        vector< vector<ofSoundPlayer> > SoundsLoop;
    
        vector<string> SoundNames;
    int sound_num;
    int sound_pos;
    
    //float sikii = 0.01;
    //int Ivolume = 20;
    //int Ispeed = 20;
    float sikii = 0.0001;
    int Ivolume = 2000;
    int Ispeed = 2000;
    
    bool bNeko;
    
    int sound_id;
    bool bRenzoku;//
    bool bMulti;//
    
    //ofxOscReceiver receiver;
    string msg_string;
    
    //GUI
    ofParameter<int>  _th;
    //ofParameter<float> paradiflevel;//差分画像のゲイン
    //ofParameter<float> paralevel;
    //ofParameter<float> parameshlevel;
    //ofParameter<int>   parasoundthr;
    //ofParameter<int>   parasoundcount;
    //ofParameter<float>   parasendvalue;

    /*ofxFloatSlider paradiflevel;//差分画像のゲイン
    ofxFloatSlider paralevel;
    ofxFloatSlider parameshlevel;
    ofxIntSlider parasoundthr;
    ofxIntSlider parasoundcount;
    ofxFloatSlider parasendvalue;*/

    float paradiflevel;//差分画像のゲイン
    float paralevel;
    float parameshlevel;
    int parasoundthr;
    int parasoundcount;
    float parasendvalue;

    
    /*ofParameter<float> paraSmooth;
    ofParameter<float> paralevelL;
    ofParameter<float> paralevelR;
    ofParameter<float> paraThr;
    ofParameter<int> paraSpeedL;
    ofParameter<int> paraSpeedR;
    ofParameter<int> paraVolumeL;
    ofParameter<int> paraVolumeR;

    ofParameter<int> paralimit;
	*/

    float spbuf;
    float thrbuf;
    
    //ofxPanel gui;
    bool bHideGui;
    bool bkill;
    
    vector<ofSoundPlayer> OSCSounds;
    vector<string> SoundList;
    
    int idOSC;
    bool bOSCmode;
    bool bdebug;
    bool blimit;//„Éè„Ç¶„É™„É≥„Ç∞Èò≤Ê≠¢
    int limitcount;
    int limithit;//ÈÄ£Á∂ö„Åó„Å¶Âè©„Åã„Çå„Å¶„ÅüÂõûÊï∞
    int tapnum;
    bool LRdetect;//L true R false
    ofxOscSender sender;

	RASPIVID_CONFIG * config;
	RaspiCamCvCapture * capture;

	int f_SumGrayImage;
	int f_SumGrayImagePre;
	int i_SumGrayImageLine;
	bool b_CameraAlive;
	int i_CameraAliveCount;
};
