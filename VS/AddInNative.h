#ifndef __ADDINNATIVE_H__
#define __ADDINNATIVE_H__

#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"

#include <string>

///////////////////////////////////////////////////////////////////////////////
// class CAddInNative
class CAddInNative : public IComponentBase
{
public:
    enum Props
    {
        ePropPort = 0,
        ePropBaud,
		ePropIsOpen,
		ePropLastCmd,
    	ePropLastAns,
    	ePropLastError,
    	ePropLastErrorText,
		ePropVersion,
		ePropLast      // Always last
    };

    enum Methods
    {
        eMethOpenPort = 0,
        eMethClosePort,
		eMethTest,
		eMethLoging,
		eMethCMD,
		eMethSetCnt,
        eMethLast      // Always last
    };

    CAddInNative(void);
    virtual ~CAddInNative();
    // IInitDoneBase
    virtual bool ADDIN_API Init(void*);
    virtual bool ADDIN_API setMemManager(void* mem);
    virtual long ADDIN_API GetInfo();
    virtual void ADDIN_API Done();
    // ILanguageExtenderBase
    virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T**);
    virtual long ADDIN_API GetNProps();
    virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
    virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
    virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
    virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
    virtual bool ADDIN_API IsPropReadable(const long lPropNum);
    virtual bool ADDIN_API IsPropWritable(const long lPropNum);
    virtual long ADDIN_API GetNMethods();
    virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
    virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum, 
                            const long lMethodAlias);
    virtual long ADDIN_API GetNParams(const long lMethodNum);
    virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
                            tVariant *pvarParamDefValue);   
    virtual bool ADDIN_API HasRetVal(const long lMethodNum);
    virtual bool ADDIN_API CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray);
    virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
    // LocaleBase
    virtual void ADDIN_API SetLocale(const WCHAR_T* loc);
    
private:
    long findName(wchar_t* names[], const wchar_t* name, const uint32_t size) const;
    void addError(uint32_t wcode, const wchar_t* source, 
                    const wchar_t* descriptor, long code);

	bool wstring_to_p(std::wstring s, tVariant* val) ;

	bool CMD(tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
	bool Test(tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray) ;
	
	uint8_t send_data(void) ;
	uint8_t OpenPort(void) ;
	void ClosePort(void) ;
	uint8_t return_error(uint8_t err_no) ;
	void write_log(char* OUTBUFFER, int l, char log_type) ;

	// Attributes
    IAddInDefBase      *m_iConnect;
    IMemoryManager     *m_iMemory;

    uint8_t             m_port;
    uint8_t             m_err;
	uint32_t            m_baud;
	int					m_cnt;
    bool                m_isOpen;
	bool				m_loging;

	std::wstring		m_cmd;
	std::wstring		m_ans;

};

#endif //__ADDINNATIVE_H__
