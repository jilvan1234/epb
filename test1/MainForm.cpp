﻿// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainForm.h"
#include <boost/thread/thread.hpp>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <string>
#include <boost/lexical_cast.hpp>

#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

#include "sqlite3.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

void SoundPlay(long index);
int Load_WAV();
void btntest();
void dbview();

struct sound {
	IGraphBuilder *pGraphBuilder;
	IMediaControl *pMediaControl;
	IMediaSeeking *pMediaSeeking;
	IMediaEventEx *pMediaEventEx;
	WCHAR wFileName[256];
	char totalTime[256];
	LONGLONG totalDuration;
	LONGLONG lDuration100NanoSecs;
	float step;
	long temporary;
	char szFileName[256];
};

sound *Sound;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	CoInitialize(NULL);
	if (Load_WAV() != 0)
		exit(0);

}
// ---------------------------------------------------------------------------

void hello_world() {
	boost::progress_timer t;
	int elapsed_time = t.elapsed();

	// std::string thing = boost::lexical_cast <std::string> (elapsed_time);
	// MessageBoxA(NULL,thing.c_str() , "oo", MB_OK);
	// MessageBoxA(NULL, "c", "oo", MB_OK);
	if (elapsed_time == 0) {
		SoundPlay(0);
		MessageBoxA(NULL, "c", "oo", MB_OK);
	}

}

void __fastcall TForm1::FormCreate(TObject *Sender) {
	SoundPlay(1);
	Timer1 = new TTimer(this);
	Timer1->Interval = 41000;
	Timer1->OnTimer = Timer1Timer;
	Timer1->Enabled = true;

	Image2->Visible = false;
	Image3->Visible = false;
	Image4->Visible = false;
	Image5->Visible = false;

	Edit1->Visible = false;
	Edit2->Visible = false;

	// BitmapListAnimation1->Stop();

	// Role1_1->Start();

	// Edit1->Visible = false;
	// Edit2->Visible = false;
	// boost::progress_timer t;
	// t.restart();
	// wchar_t *wav_handle;
	// HRSRC h = FindResource(HInstance, L"IDR_WAVE1", L"WAV");
	// HGLOBAL h1 = LoadResource(HInstance, h);
	// wav_handle = (wchar_t *)LockResource(h1);
	// sndPlaySound(wav_handle, SND_MEMORY | SND_ASYNC | SND_LOOP);

	// Sound[0].pMediaControl->Stop();
	// SoundPlay(1);

	// BitmapListAnimation1 = new TBitmapListAnimation();
}

// ---------------------------------------------------------------------------

enum GameState {
	GAME_STATE_LOGO = 0, GAME_STATE_TRAILER, GAME_STATE_MAIN_MENU,
	GAME_STATE_INGAME, GAME_STATE_SETTINGS_MENU, GAME_STATE_MAP_MAP1,
};

static int gameState = GAME_STATE_LOGO;

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	System::WideChar &KeyChar, TShiftState Shift) {
	static int shopslect = 1;
	switch (gameState) {

	case GAME_STATE_LOGO: {
			if (Key == VK_RETURN) {
				SoundPlay(2);
				BitmapListAnimation1->Stop();
				BitmapListAnimation2->Start();
				// Timer1->Enabled = true;
				// btntest();
				gameState = GAME_STATE_TRAILER;

			}

			if (Key == VK_ESCAPE) {
				SoundPlay(2);
				BitmapListAnimation1->Stop();
				// BitmapListAnimation2->Start();
				// Timer1->Enabled = true;
				// btntest();
				gameState = GAME_STATE_TRAILER;

				Sleep(100);

				// dbview();
				Timer1->Enabled = false;
				Sound[1].pMediaControl->Stop();
				SoundPlay(2);

				Sleep(100);

				BitmapListAnimation2->Stop();
				BitmapListAnimation3->Stop();
				// BitmapListAnimation4->Start();
				gameState = GAME_STATE_MAIN_MENU;

				Sleep(100);

				SoundPlay(3);
				SoundPlay(2);
				BitmapListAnimation4->Stop();
				// BitmapAnimation1->Start();
				gameState = GAME_STATE_INGAME;

				Sleep(100);

				Sound[3].pMediaControl->Stop();
				SoundPlay(4);
				BitmapAnimation1->Stop();
				// shop1->Start();
				gameState = GAME_STATE_SETTINGS_MENU;

				Sleep(100);
				SoundPlay(2);
				// Configuration1_1->Start();
				shopslect = 6;

				SoundPlay(2);
				Sound[4].pMediaControl->Stop();
				Configuration1_5->Stop();
				Sleep(100);

				// map1->Start();
				gameState = GAME_STATE_MAP_MAP1;
				SoundPlay(5);

				Image1->Visible = false;
				Image5->Visible = true;

				Image6->Visible = true;

				Image6->Position->X = 510;
				Image6->Position->Y = 850;

				Role1_1->Start();

				Image5->Position->X = -230;
				Image5->Position->Y = -630;

			}

			// sndPlaySound(NULL,NULL);
			// wchar_t *wav_handle;
			// HRSRC h = FindResource(HInstance, L"IDR_WAVE2", L"WAV");
			// HGLOBAL h1 = LoadResource(HInstance, h);
			// wav_handle = (wchar_t *)LockResource(h1);
			// sndPlaySound(wav_handle, SND_MEMORY | SND_ASYNC);

		} break;

	case GAME_STATE_TRAILER: {

			if (Key == VK_UP) {
				SoundPlay(0);
				BitmapListAnimation3->Stop();
				BitmapListAnimation2->Start();
			}
			if (Key == VK_DOWN) {
				SoundPlay(0);
				BitmapListAnimation2->Stop();
				BitmapListAnimation3->Start();
			}
			if (Key == VK_RETURN) {
				// dbview();
				Timer1->Enabled = false;
				Sound[1].pMediaControl->Stop();
				SoundPlay(2);

				BitmapListAnimation2->Stop();
				BitmapListAnimation3->Stop();
				BitmapListAnimation4->Start();
				gameState = GAME_STATE_MAIN_MENU;
			}

			break;
		}
	case GAME_STATE_MAIN_MENU: {
			if (Key == VK_RETURN) {
				SoundPlay(3);
				SoundPlay(2);
				BitmapListAnimation4->Stop();
				BitmapAnimation1->Start();
				gameState = GAME_STATE_INGAME;
			}
			break;
		}
	case GAME_STATE_INGAME: {
			if (Key == VK_RETURN) {
				Sound[3].pMediaControl->Stop();
				SoundPlay(4);
				BitmapAnimation1->Stop();
				shop1->Start();
				gameState = GAME_STATE_SETTINGS_MENU;
			}

			break;
		}
	case GAME_STATE_SETTINGS_MENU: {
			static int Configurationselect = 1;
			switch (shopslect) {
			case 1: {
					if (Key == VK_UP) {
						SoundPlay(0);
						shopslect = 1;
					}
					if (Key == VK_DOWN) {
						SoundPlay(0);
						shop1->Stop();
						shop2->Start();
						shopslect = 2;
					}
					if (Key == VK_RETURN) {
						SoundPlay(2);
						Rose1->Start();
						shopslect = 5;
					}

				} break;
			case 2: {
					if (Key == VK_UP) {
						SoundPlay(0);
						shop2->Stop();
						shop1->Start();
						shopslect = 1;
					}
					if (Key == VK_DOWN) {
						SoundPlay(0);
						shop2->Stop();
						shop3->Start();
						shopslect = 3;
					}
				} break;
			case 3: {
					if (Key == VK_UP) {
						SoundPlay(0);
						shop3->Stop();
						shop2->Start();
						shopslect = 2;
					}
					if (Key == VK_DOWN) {
						SoundPlay(0);
						shop3->Stop();
						shop4->Start();
						shopslect = 4;
					}
				} break;
			case 4: {
					if (Key == VK_UP) {
						SoundPlay(0);
						shop4->Stop();
						shop3->Start();
						shopslect = 3;
					}
					if (Key == VK_DOWN) {
						SoundPlay(0);
						shopslect = 4;
					}
					if (Key == VK_RETURN) {
						SoundPlay(2);
						Configuration1_1->Start();
						shopslect = 6;
					}
				} break;
			case 5: {
					if (Key == VK_UP) {
						SoundPlay(0);
						Rose1->Start();
						Rose2->Stop();
					}
					if (Key == VK_DOWN) {
						SoundPlay(0);
						Rose1->Stop();
						Rose2->Start();
					}
					if (Key == VK_ESCAPE) {
						SoundPlay(0);
						Rose1->Stop();
						Rose2->Stop();
						shop1->Start();
						shopslect = 1;
					}
				} break;
			case 6: {
					switch (Configurationselect) {
					case 1: {
							if (Key == VK_UP) {
								SoundPlay(0);
								Configurationselect = 1;
							}
							if (Key == VK_DOWN) {
								SoundPlay(0);
								Configuration1_1->Stop();
								Configuration1_2->Start();
								Configurationselect = 2;
							}

							if (Key == VK_ESCAPE) {
								SoundPlay(0);
								Configuration1_1->Stop();
								shop1->Start();
								shopslect = 1;
							}

						} break;
					case 2: {
							if (Key == VK_UP) {
								SoundPlay(0);
								Configuration1_1->Start();
								Configuration1_2->Stop();
								Configurationselect = 1;
							}
							if (Key == VK_DOWN) {
								SoundPlay(0);
								Configuration1_2->Stop();
								Configuration1_3->Start();
								Configurationselect = 3;
							}
							if (Key == VK_ESCAPE) {
								SoundPlay(0);
								Configuration1_1->Stop();
								shop1->Start();
								shopslect = 1;
							}

						} break;
					case 3: {
							if (Key == VK_UP) {
								SoundPlay(0);
								Configuration1_2->Start();
								Configuration1_3->Stop();
								Configurationselect = 2;
							}
							if (Key == VK_DOWN) {
								SoundPlay(0);
								Configuration1_3->Stop();
								Configuration1_4->Start();
								Configurationselect = 4;
							}
							if (Key == VK_ESCAPE) {
								SoundPlay(0);
								Configuration1_1->Stop();
								shop1->Start();
								shopslect = 1;
							}

						} break;
					case 4: {
							if (Key == VK_UP) {
								SoundPlay(0);
								Configuration1_3->Start();
								Configuration1_4->Stop();
								Configurationselect = 3;
							}
							if (Key == VK_DOWN) {
								SoundPlay(0);
								Configuration1_4->Stop();
								Configuration1_5->Start();
								Configurationselect = 5;
							}
							if (Key == VK_ESCAPE) {
								SoundPlay(0);
								Configuration1_1->Stop();
								shop1->Start();
								shopslect = 1;
							}

						} break;
					case 5: {
							if (Key == VK_UP) {
								SoundPlay(0);
								Configuration1_4->Start();
								Configuration1_5->Stop();
								Configurationselect = 4;
							}
							if (Key == VK_DOWN) {
								SoundPlay(0);
								Configuration1_5->Stop();
								Configurationselect = 5;
							}
							if (Key == VK_ESCAPE) {
								SoundPlay(0);
								Configuration1_1->Stop();
								shop1->Start();
								shopslect = 1;
							}

							if (Key == VK_RETURN) {
								SoundPlay(2);
								Sound[4].pMediaControl->Stop();
								Configuration1_5->Stop();
								map1->Start();
								gameState = GAME_STATE_MAP_MAP1;
								SoundPlay(5);
							}

						} break;
					default: {

						} break;
					}

				} break;
			default: {

				} break;
			}

			break;
		}
	case GAME_STATE_MAP_MAP1: {

			if (Key == VK_UP) {
				if (Image5->Position->Y < 0)
					Image5->Position->Y += 10;
			}
			if (Key == VK_DOWN) {
				if (Image5->Position->Y > -700)
					Image5->Position->Y -= 10;
			}
			if (Key == VK_LEFT) {
				if (Image5->Position->X < 0)
					Image5->Position->X += 10;
			}
			if (Key == VK_RIGHT) {
				if (Image5->Position->X > -870)
					Image5->Position->X -= 10;
			}
			Edit1->Text = Image5->Position->X;
			Edit2->Text = Image5->Position->Y;

		} break;
	default: {
			break;
		}
	}

	// if (Key == VK_ESCAPE)
	// exit(0);
}
// ---------------------------------------------------------------------------

int Load_WAV() {

	HRESULT hr;
	char * str[6] =
		// {"annu6.wav", "gtitle.wav", "ko1.wav", "title1.wav", "shop1.wav","map1.wav"};
	{"C:\\c++\\epbgit\\test1\\annu6.wav", "C:\\c++\\epbgit\\test1\\gtitle.wav",
		"C:\\c++\\epbgit\\test1\\ko1.wav", "C:\\c++\\epbgit\\test1\\title1.wav",
		"C:\\c++\\epbgit\\test1\\shop1.wav", "C:\\c++\\epbgit\\test1\\map1.wav"
	};

	// char *wav_handle[2];
	// HRSRC h = FindResource(HInstance, L"IDR_WAVE1", L"WAV");
	// HGLOBAL h1 = LoadResource(HInstance, h);
	// wav_handle[0] = (char *)LockResource(h1);
	// sndPlaySound(wav_handle, SND_MEMORY | SND_ASYNC | SND_LOOP);

	Sound = new sound[6];

	for (int i = 0; i < 6; i++) {
		strcpy_s(Sound[i].szFileName, 256, str[i]);
		// strcpy_s(Sound[i].szFileName, 256, wav_handle[i]);
	}
	wchar_t wFileName[256];
	for (int i = 0; i < 6; i++) {
		mbstowcs(wFileName, Sound[i].szFileName, 256);
		Sound[i].pGraphBuilder = NULL;
		Sound[i].pMediaControl = NULL;
		Sound[i].pMediaSeeking = NULL;
		Sound[i].pMediaEventEx = NULL;

		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void**)&Sound[i].pGraphBuilder);
		if (SUCCEEDED(hr)) {
			hr = Sound[i].pGraphBuilder->QueryInterface(IID_IMediaControl,
				(void **)&Sound[i].pMediaControl);
			hr = Sound[i].pGraphBuilder->QueryInterface(IID_IMediaSeeking,
				(void**)&Sound[i].pMediaSeeking);
			hr = Sound[i].pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(void**)&Sound[i].pMediaEventEx);
			Sound[i].pGraphBuilder->RenderFile(wFileName, NULL);
			Sound[i].pMediaSeeking->GetDuration(&Sound[i].lDuration100NanoSecs);
			Sound[i].totalDuration = Sound[i].lDuration100NanoSecs / 10000000;
			Sound[i].temporary = (long)Sound[i].totalDuration;
			if (Sound[i].temporary == 0) {
			}
			else
				Sound[i].step = (float)100 / Sound[i].temporary;
		}

	}

	return 0;
}

void SoundPlay(long index) {
	LONGLONG start = 0;
	if (Sound[index].pMediaSeeking) {
		Sound[index].pMediaSeeking->SetPositions(&start,
			AM_SEEKING_AbsolutePositioning, &Sound[index].lDuration100NanoSecs,
			AM_SEEKING_AbsolutePositioning);
		Sound[index].pMediaControl->Run();
	}

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {
	try {
		// int ccc = t.elapsed();
		// std::string thing = boost::lexical_cast<std::string>(ccc);
		// MessageBox(NULL, thing.c_str(), L"oo", MB_OK);
		SoundPlay(1);
		// Sound[0].pMediaControl->Stop();
		// MessageBoxA(NULL, "c", "oo", MB_OK);
		// boost:: thread my_thread(&hello_world);
		// my_thread.join();

	}
	catch (Exception &e) {
		ShowMessage(e.Message);
	}
}

void btntest() {

	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	rc = sqlite3_open("dice.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else {
	}

	int nrow = 0, ncolumn = 0;
	char ch1[4096] =
		"CREATE TABLE SensorData(ID INTEGER PRIMARY KEY,ROSENAME VARCHAR(12),ROSEID INTEGER );";
	sql = ch1;
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	char aa[4096] = "INSERT INTO \"SensorData\" VALUES( NULL ,'1', 2);";

	sql = aa;
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	sqlite3_close(db);

}

void dbview() {
	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	rc = sqlite3_open("dice.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else {
	}

	char aa[1024] = "select * from SensorData;";
	int nrow = 0, ncolumn = 0;
	char **azResult; // 二維數組存放結果

	sql = aa;
	// MessageBoxA(NULL, "cc", "oo", MB_OK);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	for (int i = 0; i < (nrow + 1) * ncolumn; i++) {
		// std::cout << azResult[i] << std::endl;
		MessageBoxA(NULL, azResult[i], "oo", MB_OK);
	}
	sqlite3_free_table(azResult);
	sqlite3_close(db);
}

// ---------------------------------------------------------------------------
