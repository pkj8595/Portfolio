#include "Stdafx.h"
#include "PlayerStatusUI.h"

HRESULT PlayerStatusUI::init(CPlayer_Attribute* status, int* level, float* skillCool)
{
	_layout = IMAGEMANAGER->addImage("StatusUI", "Resource/Images/Lucie/CompleteImg/UI/Layout.bmp", 230, 90, true, RGB(255,0,255));
	_exp = IMAGEMANAGER->addImage("Exp", "Resource/Images/Lucie/CompleteImg/UI/EXP_Meter.bmp", 126, 7, true, RGB(255,0,255));
	_stamina = IMAGEMANAGER->addImage("Stamina", "Resource/Images/Lucie/CompleteImg/UI/TP_Meter.bmp", 166, 14, true, RGB(255,0,255));
	_levelImage = IMAGEMANAGER->addFrameImage("Level", "Resource/Images/Lucie/CompleteImg/UI/LV_Number.bmp", 320, 19, 10, 1, true, RGB(255,0,255));
	_hp = IMAGEMANAGER->addFrameImage("Hp", "Resource/Images/Lucie/CompleteImg/UI/HP_Icon.bmp", 72, 22, 3, 1, true, RGB(255,0,255));
	_maxHp = IMAGEMANAGER->addFrameImage("Hp", "Resource/Images/Lucie/CompleteImg/UI/HP_Icon.bmp", 72, 22, 3, 1, true, RGB(255,0,255));
	_mp = IMAGEMANAGER->addFrameImage("Mp", "Resource/Images/Lucie/CompleteImg/UI/MP_Icon.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_maxMp = IMAGEMANAGER->addFrameImage("Mp", "Resource/Images/Lucie/CompleteImg/UI/MP_Icon.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_skillCoolNumberImage = IMAGEMANAGER->addFrameImage("Number", "Resource/Images/Lucie/CompleteImg/system/Gold_B.bmp", 140, 20, 10, 1, true, RGB(255, 0, 255));
	_skillCoolCircleImage = IMAGEMANAGER->addImage("CoolCircle", "Resource/Images/Lucie/CompleteImg/system/coolTimeCircle.bmp", 39, 39, true, RGB(255, 0, 255));
	_skillIcon = IMAGEMANAGER->addImage("SkillIcon", "Resource/Images/Lucie/CompleteImg/UI/Skill.bmp", 32, 32, true, RGB(255,0,255));
	_status = status;
	_level = level;
	_skillCool = skillCool;

	_pos.x = CAMERAMANAGER->getDisplayCenterX() - 115;
	_pos.y = CAMERAMANAGER->getDisplayAreaBottom() - 120;

	return S_OK;
};
HRESULT PlayerStatusUI::init(CPlayer_Attribute* status, int* level)
{
	_layout = IMAGEMANAGER->addImage("StatusUI", "Resource/Images/Lucie/CompleteImg/UI/Layout.bmp", 230, 90, true, RGB(255, 0, 255));
	_exp = IMAGEMANAGER->addImage("Exp", "Resource/Images/Lucie/CompleteImg/UI/EXP_Meter.bmp", 126, 7, true, RGB(255, 0, 255));
	_stamina = IMAGEMANAGER->addImage("Stamina", "Resource/Images/Lucie/CompleteImg/UI/TP_Meter.bmp", 166, 14, true, RGB(255, 0, 255));
	_levelImage = IMAGEMANAGER->addFrameImage("Level", "Resource/Images/Lucie/CompleteImg/UI/LV_Number.bmp", 320, 19, 10, 1, true, RGB(255, 0, 255));
	_hp = IMAGEMANAGER->addFrameImage("Hp", "Resource/Images/Lucie/CompleteImg/UI/HP_Icon.bmp", 72, 22, 3, 1, true, RGB(255, 0, 255));
	_maxHp = IMAGEMANAGER->addFrameImage("Hp", "Resource/Images/Lucie/CompleteImg/UI/HP_Icon.bmp", 72, 22, 3, 1, true, RGB(255, 0, 255));
	_mp = IMAGEMANAGER->addFrameImage("Mp", "Resource/Images/Lucie/CompleteImg/UI/MP_Icon.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_maxMp = IMAGEMANAGER->addFrameImage("Mp", "Resource/Images/Lucie/CompleteImg/UI/MP_Icon.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_skillCoolNumberImage = IMAGEMANAGER->addFrameImage("Number", "Resource/Images/Lucie/CompleteImg/system/Gold_B.bmp", 140, 20, 10, 1, true, RGB(255, 0, 255));
	_skillCoolCircleImage = IMAGEMANAGER->addImage("CoolCircle", "Resource/Images/Lucie/CompleteImg/system/coolTimeCircle.bmp", 39, 39, true, RGB(255, 0, 255));
	_skillIcon = IMAGEMANAGER->addImage("SkillIcon", "Resource/Images/Lucie/CompleteImg/UI/Skill.bmp", 32, 32, true, RGB(255, 0, 255));

	_status = status;
	_level = level;

	_pos.x = CAMERAMANAGER->getDisplayCenterX() - 115;
	_pos.y = CAMERAMANAGER->getDisplayAreaBottom() - 120;

	return S_OK;
};

void PlayerStatusUI::release(void)
{
}

void PlayerStatusUI::update(void)
{
	_staminaWidth = _stamina->getWidth() * (_status->_stamina / _status->_maxStamina);
	_expWidth = _exp->getWidth() * (_status->_experience / _status->_maxExperience);
}

void PlayerStatusUI::render(void)
{
	_stamina->render(getMemDC(), _pos.x + 27, _pos.y + 63, 0, 0, _staminaWidth, _stamina->getHeight());
	_exp->render(getMemDC(), _pos.x + 63, _pos.y + 50, 0, 0, _expWidth, _exp->getHeight());
	_layout->render(getMemDC(), _pos.x, _pos.y);
	hpRender();
	mpRender();
	_levelImage->frameRender(getMemDC(), _pos.x + 20, _pos.y + 40, *_level, _levelImage->getFrameY());
	skillCoolRender();

}

void PlayerStatusUI::hpRender(void)
{
	int maxHpSlotAmount = (_status->_maxHp % 2 == 1) ? (_status->_maxHp + 1) / 2 : _status->_maxHp / 2;
	for (int i = 0; i < maxHpSlotAmount; i++)
	{
		_maxHp->frameRender(getMemDC(), _pos.x + 55 - (i * 26), _pos.y + 18, 0, 0);
	}
	int hpSlotAmount = (_status->_hp % 2 == 1) ? (_status->_hp + 1) / 2 : _status->_hp / 2;
	for (int i = 0; i < hpSlotAmount; i++)
	{
		if (i == hpSlotAmount - 1)
		{
			if (_status->_hp % 2 == 1)
			{
				_hp->frameRender(getMemDC(), _pos.x + 55 - (i * 26), _pos.y + 18, 2, 0);
			}
			else _hp->frameRender(getMemDC(), _pos.x + 55 - (i * 26), _pos.y + 18, 1, 0);
		}
		else _hp->frameRender(getMemDC(), _pos.x + 55 - (i * 26), _pos.y + 18, 1, 0);
	}
}

void PlayerStatusUI::mpRender(void)
{
	for (int i = 0; i < _status->_maxMana; i++)
	{
		_maxMp->frameRender(getMemDC(), _pos.x + 140 + (i * 26), _pos.y + 18, 0, 0);
	}
	for (int i = 0; i < _status->_mana; i++)
	{
		_mp->frameRender(getMemDC(), _pos.x + 140 + (i * 26), _pos.y + 18, 1, 0);
	}
}

void PlayerStatusUI::skillCoolRender(void)
{
	_skillIcon->render(getMemDC(), _pos.x + 94, _pos.y + 7);
	if (getCoolTime() > 0)
	{
		_skillCoolCircleImage->alphaRender(getMemDC(), _pos.x + 90, _pos.y, 120);
		if (getCoolTime() == 10)
		{
			_skillCoolNumberImage->frameRender(getMemDC(), _pos.x + 95, _pos.y + 13, 1, 0);
			_skillCoolNumberImage->frameRender(getMemDC(), _pos.x + 110, _pos.y + 13, 0, 0);
		}
		else
		{
			_skillCoolNumberImage->frameRender(getMemDC(), _pos.x + 102, _pos.y + 13, getCoolTime(), 0);
		}
	}
}

