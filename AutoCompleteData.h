#include <iostream>

using namespace std;

class AutoCompleteData
{
public:
	AutoCompleteData(string completed, string source, int offset, int score):
	m_completed_sentence(completed), m_source_text(source), m_offset(offset), m_score(score)
	{}

	bool operator > (const AutoCompleteData& obj) const
    {
        return (m_score > obj.getScore());
    }

    int getScore() const
    {
    	return m_score;
    }

    string getCompleted() const
    {
    	return m_completed_sentence;
    }

    string getSource() const
    {
    	return m_source_text;
    }

    int getOffset() const
    {
    	return m_offset;
    }


private:
	std::string m_completed_sentence;
	std::string m_source_text;
	int m_offset;
	int m_score;
};