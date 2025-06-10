#ifndef __INC_BUFF_ON_ATTRIBUTES_H__
#define __INC_BUFF_ON_ATTRIBUTES_H__

class CHARACTER;

class CBuffOnAttributes
{
public:
	CBuffOnAttributes(LPCHARACTER pOwner, POINT_TYPE wPointType, std::vector<POINT_TYPE>* vec_pBuffWearTargets);
	~CBuffOnAttributes();

	// ���� �� �̸鼭, m_vec_pBuffWearTargets �� �ش��ϴ� �������� ���, �ش� ���������� ���� ���� ȿ���� ����.
	void RemoveBuffFromItem(LPITEM pItem);
	// m_vec_pBuffWearTargets �� �ش��ϴ� �������� ���, �ش� �������� attribute �� ���� ȿ�� �߰�.
	void AddBuffFromItem(LPITEM pItem);
	// m_llBuffValue�� �ٲٰ�, ������ ���� �ٲ�.
	void ChangeBuffValue(POINT_VALUE lNewValue);
	// CHRACTRE::ComputePoints���� �Ӽ�ġ�� �ʱ�ȭ�ϰ� �ٽ� ����ϹǷ�, 
	// ���� �Ӽ�ġ���� ���������� owner���� ��.
	void GiveAllAttributes();

	// m_vec_pBuffWearTargets �� �ش��ϴ� ��� �������� attribute�� type���� �ջ��ϰ�,
	// �� attribute���� (m_llBuffValue)% ��ŭ�� ������ ��.
	bool On(POINT_VALUE dwValue);
	// ���� ���� ��, �ʱ�ȭ
	void Off();

	void Initialize();

private:
	LPCHARACTER m_pBuffOwner;
	POINT_TYPE m_wPointType;
	POINT_VALUE m_lBuffValue;
	std::vector<POINT_TYPE>* m_vec_pBuffWearTargets;

	// apply_type, apply_value ����� ��
	typedef std::map<POINT_TYPE, POINT_VALUE> TMapAttr;
	// m_vec_pBuffWearTargets �� �ش��ϴ� ��� �������� attribute �� type���� �ջ��Ͽ� ������ ����.
	TMapAttr m_map_AdditionalAttrs;
};

#endif // __INC_BUFF_ON_ATTRIBUTES_H__
