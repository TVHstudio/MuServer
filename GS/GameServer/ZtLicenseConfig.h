#pragma once

struct USER_MedoniAndrei
{
	int GateMapNumber;
	int GateMapX;
	int GateMapY;
};

class CZtLicenseConfig
{
public:
		CZtLicenseConfig();
		~CZtLicenseConfig();

	void Load();

	void ReadMedoniAndrei(char* filename);

	USER_MedoniAndrei m_MedoniAndrei;
};

extern CZtLicenseConfig g_ZtLicenseConfig;