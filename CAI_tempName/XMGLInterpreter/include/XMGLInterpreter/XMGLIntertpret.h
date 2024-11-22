#pragma once
#include "XMGL.h"
#include "XMGLNode/XMGLNode.h"
#include "XMGLAbstractExpression.h"
#include <vector>
#include <stack>
/// <summary>
/// 针对与xml格式数据的解析，该架构以数据文本内容含义为基准：不同文本表达不同含义 ex:< nodeName  propertyName> 将上面的
/// 解析，步骤为，以整体为起始，从左至右依次读取 即 tag标签---> [tag类型 ---> tag 名称] ---> [tag属性表达式--->{tag属性名称 ---> tag属性值}]
/// 以括号为一个整体，每个整体无法解析的字符将向上传递，每个阶段无法解析的字符会终止本阶段的解析，并将该字符转交给上父阶段处理。如果所有阶段
/// 均无法处理那么，将不在进行解析步骤
/// </summary>		
namespace XMGL {
	////char字符过滤器
	//class XMGLCharFilter {
	//public:
	//	enum {
	//		Default = bit(0),
	//		None = bit(1),
	//		Letters = bit(2),
	//		Numbers = bit(3),
	//		SpecificChars = bit(4),
	//	};
	//public:
	//	bool Filt(const char& chr) {
	//		
	//	}
	//public:
	//	std::vector<char> expectChars;

	//};

	class XMGLExpression : public XMLAbstractExpression {
	public:
		inline bool IsSpaceChar(const char& chr);
		inline bool IsLetter(const char& chr);
		inline bool IsNumber(const char& chr);
		bool errorOccurred = false;
	protected:
		void SkipSpaceChar(const char*& str, Tag& tag);
		void RaiseError(const AbstractError& error) override;
	};

	class XMLTagNameExpression : public XMGLExpression {
	public:
		XMLTagNameExpression() = default;
		~XMLTagNameExpression() = default;
		bool Interpret(const char*& str, Tag& tag) override;
	private:
		inline bool SetTagType(const char*& str,Tag& tag);
		inline bool VertifyCharValidation(const char& chr);
		bool LoadName(const char*& str, Tag& tag);
	};

	class XMGLPropertyNameExpression : public XMGLExpression {
	public:
		XMGLPropertyNameExpression() = default;
		~XMGLPropertyNameExpression() = default;
		bool Interpret(const char*& str, Tag& tag) override;
	private:
		inline bool HandleSpecialChar(const char*& str, Tag& tag);
		inline bool VertifyCharValidation(const char& chr);
	public:
		std::string name;
	};

/// <summary>
/// XML双引号解析，这是一个终结表达式
/// </summary>
	class XMGLPropertyValueExpression : public XMGLExpression {
	public:
		XMGLPropertyValueExpression() = default;
		~XMGLPropertyValueExpression() = default;
		// 通过 AbstractExpression 继承
		bool Interpret(const char*& str, Tag& tag) override;
	private:
		inline bool HandleSpecialChar(const char*& str, Tag& tag);
		inline bool VertifyCharValidation(const char& chr);
	public:
		std::string value;
	};

	/// <summary>
	/// XML属性解析---这不是一个终结表达式。本身存储了两个终结表达式
	/// 属性表达式只有以下有效形式   propertyName空白字符=空白字符value
	/// </summary>
	class XMGLPropertyExpression : public XMGLExpression {
	public:
		XMGLPropertyExpression() = default;
		~XMGLPropertyExpression() = default;
		// 通过 AbstractExpression 继承
		bool Interpret(const char*& str, Tag& tag) override;
		inline bool HandleSpecialChar(const char*& str, Tag& tag);
	private:
		XMGLPropertyNameExpression pNameExpr;
		XMGLPropertyValueExpression pValueExp;
		//不期望出现的字符
		//std::vector<char> unexpectChars;
	};

	/// <summary>
	/// XML节点属性解析
	/// </summary>
	class XMGLTagExpression : public XMGLExpression {
	public:

		XMGLTagExpression() = default;
		~XMGLTagExpression() = default;
		// 通过 AbstractExpression 继承
		bool Interpret(const char*& str, Tag& tag) override;
	private:
		//特殊字符处理,也就是终止符处理，只要是特殊字符都是对本操作的结束提示
		inline bool HandleSpecialChar(const char*& str, Tag& tag);
	private:
		XMGLPropertyExpression proExpr;
		XMLTagNameExpression tNameExpr;
		bool matchStatus = false;
		bool hasbeenClose = false;
	};

	class XMGLInterpret : public XMGLExpression {
	public:
		XMGLInterpret() = default;
		~XMGLInterpret() = default;
		// 通过 XMGLExpression 继承
		bool Interpret(const char*& str, Tag& tag) override;
	public:
		inline auto& GetTags() const { return tags; }
	private:
		bool AddTag(Tag& tag);
		bool LoadPcData(const char*& str);
		inline bool VertifyCharValidation(const char& chr);
	private:
		XMGLTagExpression tagExpr;
		std::stack<std::shared_ptr<Tag>> unPairTags;
		std::vector<std::shared_ptr<Tag>> tags;
		size_t line =1;
		size_t column =1;
	};

	/// <summary>
	/// XML解释器：控制解释流程，错误处理等
	/// </summary>
	class DLLAPI XMLInterpreter {
	public:
		XMLInterpreter() = default;
		//处理错误
		//void OnXMLErrorOccured(const AbstractError& e);
		void start(const char* data);
		void toString(const std::shared_ptr<Tag>& tag);
	private:
		XMGLInterpret tExpr;
	};

}
