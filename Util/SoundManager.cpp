#include "SoundManager.h"
#include "Game.h"
#include <cassert>

namespace
{
	constexpr char sound_file_signature[] = "SND_";
	constexpr char sound_config_file_path[] = "./sound.conf";
	constexpr float sound_config_version = 1.0f;
}

void SoundManager::LoadSoundConfig()
{
	SoundConfigInfo conf = {};
	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "rb");
	if (fp)
	{
		fread(&conf, sizeof(conf), 1, fp);
		fclose(fp);
		m_volumeBGM = conf.volumeBGM;
		m_volumeSE = conf.volumeSE;
	}
	else
	{
		MessageBox(NULL, "プレイしていただき、ありがとうございます！", " ", MB_OK);	// メッセージボックスを使って警告表示
	}
}

void SoundManager::SaveSoundConfig()
{
	SoundConfigInfo conf = {};
	memcpy_s(conf.signature, sizeof(conf.signature), sound_file_signature, sizeof(sound_file_signature));

	conf.version = sound_config_version;
	conf.volumeSE = m_volumeSE;
	conf.volumeBGM = m_volumeBGM;

	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "wb");
	if (fp)
	{
		fwrite(&conf, sizeof(conf), 1, fp);
		fclose(fp);
	}
}

SoundManager::~SoundManager()
{
	if (CheckSoundMem(m_hCurrentMusic) == 1)
	{
		StopSoundMem(m_hCurrentMusic);
	}

	SaveSoundConfig();

	// 効果音データ
	DeleteSoundMem(m_hCurrentMusic);
	DeleteSoundMem(m_hSelectSound);
	DeleteSoundMem(m_hDamageSound);
	DeleteSoundMem(m_hDeadSound);
	DeleteSoundMem(m_hRingoSound);
	DeleteSoundMem(m_hRingo2Sound);
	DeleteSoundMem(m_hYabaiSound);
	DeleteSoundMem(m_hChinoVoice);
	DeleteSoundMem(m_hMyuVoice);
	DeleteSoundMem(m_hNinaVoice);
	DeleteSoundMem(m_hVitteVoice);
	DeleteSoundMem(m_hRaraTy);
	// 曲データ
	DeleteSoundMem(m_hMainMusic);
	DeleteSoundMem(m_hNormalMusic);
}

void SoundManager::PlaySE(SoundType sound)
{
	int volumePal = (255 / 100) * m_volumeSE;
	ChangeVolumeSoundMem(m_volumeSE, GetCurrentSoundHandle(sound));
	PlaySoundMem(GetCurrentSoundHandle(sound), DX_PLAYTYPE_BACK);
}

void SoundManager::PlayMusic(MusicType music)
{
	SetCurrentMusic(music);
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hCurrentMusic);
	PlaySoundMem(m_hCurrentMusic, DX_PLAYTYPE_BACK);
}

void SoundManager::RestartCurrentBGM()
{
	PlaySoundMem(m_hCurrentMusic, DX_PLAYTYPE_BACK, false);
}

int SoundManager::IsPlayingMusic()
{
	return CheckSoundMem(m_hCurrentMusic);
}

void SoundManager::SetSEVolume(int volume)
{
	m_volumeSE = volume;
}

int SoundManager::GetSEVolume() const
{
	return m_volumeSE;
}

void SoundManager::SetBGMVolume(int volume)
{
	m_volumeBGM = volume;
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hCurrentMusic);
}

int SoundManager::GetBGMVolume() const
{
	return m_volumeBGM;
}

void SoundManager::SetBGMRate(float rate)
{
	assert(0.0f <= rate && rate <= 1.0f);
	ChangeVolumeSoundMem(static_cast<int>(static_cast<float>(m_volumeBGM) * rate), m_hCurrentMusic);
}

void SoundManager::StopBGM()
{
	StopSoundMem(m_hCurrentMusic);
}

SoundManager::SoundManager() :
	m_hCurrentMusic(NULL),
	m_hSelectSound(-1),
	m_hDamageSound(-1),
	m_hMainMusic(-1)
{
	LoadSoundConfig();
	LoadData();
}

int SoundManager::GetCurrentSoundHandle(SoundType sound)
{
	int currentSound = -1;

	if (sound == SoundType::select)
	{
		currentSound = m_hSelectSound;
	}
	else if (sound == SoundType::damage)
	{
		currentSound = m_hDamageSound;
	}
	else if (sound == SoundType::dead)
	{
		currentSound = m_hDeadSound;
	}
	else if (sound == SoundType::ringo)
	{
		currentSound = m_hRingoSound;
	}
	else if (sound == SoundType::ringo2)
	{
		currentSound = m_hRingo2Sound;
	}
	else if (sound == SoundType::yabai)
	{
		currentSound = m_hYabaiSound;
	}
	else if (sound == SoundType::chino)
	{
		currentSound = m_hChinoVoice;
	}
	else if (sound == SoundType::myu)
	{
		currentSound = m_hMyuVoice;
	}
	else if (sound == SoundType::nina)
	{
		currentSound = m_hNinaVoice;
	}
	else if (sound == SoundType::vitte)
	{
		currentSound = m_hVitteVoice;
	}
	else if (sound == SoundType::raraty)
	{
		currentSound = m_hRaraTy;
	}


	return currentSound;
}

void SoundManager::SetCurrentMusic(MusicType music)
{
	if (music == MusicType::title)
	{
		m_hCurrentMusic = m_hNormalMusic;
	}
	else if (music == MusicType::main)
	{
		m_hCurrentMusic = m_hMainMusic;
	}
	else if (music == MusicType::over)
	{
		m_hCurrentMusic = m_hNormalMusic;
	}
}

void SoundManager::LoadData()
{
	// サウンド
	m_hSelectSound = LoadSoundMem("Data/SoundData/Select.wav");
	m_hDamageSound = LoadSoundMem("Data/SoundData/neffyuwaaa.wav");
	m_hDeadSound = LoadSoundMem("Data/SoundData/neffyuwaaaa.wav");
	m_hRingoSound = LoadSoundMem("Data/SoundData/ringo.wav");
	m_hRingo2Sound = LoadSoundMem("Data/SoundData/ringo2.wav");
	m_hYabaiSound = LoadSoundMem("Data/SoundData/rarayabai.wav");
	m_hChinoVoice = LoadSoundMem("Data/SoundData/chinodesu.wav");
	m_hMyuVoice = LoadSoundMem("Data/SoundData/myudesu.wav");
	m_hNinaVoice = LoadSoundMem("Data/SoundData/ninadesu.wav");
	m_hVitteVoice = LoadSoundMem("Data/SoundData/vittedesu.wav");
	m_hRaraTy = LoadSoundMem("Data/SoundData/raraty.wav");
	// ミュージック
	m_hMainMusic = LoadSoundMem("Data/MusicData/Music_CD.mp3");
	m_hNormalMusic = LoadSoundMem("Data/MusicData/Music_CD.mp3");
}
