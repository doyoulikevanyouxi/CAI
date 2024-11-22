#pragma once
#include<string>
#include<map>
#include<vector>
#include <memory>
namespace XMGL {
	enum XMGLTagtType {
		Information,
		//注释标签
		NoteTag,
		//普通标签
		NormalTag,
		//关闭标签
		CloseTag,
		//自闭标签
		SelfCloseTag,
		//无效标签
		InvalidTag
	};

	class Tag {
	public:
		Tag() = default;
		Tag(const Tag& other);
	public:
		bool hasChilds = false;
		bool hasPcData = false;
		XMGLTagtType tagType;
		//节点名称
		std::string nodeName;
		std::string pcData;
		std::vector<std::shared_ptr<Tag>> childs;
		size_t line;
		size_t column;
		//节点属性
		std::map<std::string, std::string> propertys;
		bool matched(Tag& other) {
			if (this->nodeName == other.nodeName) {
				if (this->tagType == NormalTag && other.tagType == CloseTag)
					return true;
				if ((this->tagType == CloseTag && other.tagType == NormalTag))
					return true;
				return false;
			}
			return false;
		}
	};
}


