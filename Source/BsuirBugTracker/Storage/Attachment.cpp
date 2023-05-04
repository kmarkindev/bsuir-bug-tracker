#include "Attachment.h"

SerializedData Attachment::Serialize() const
{
	return {};
}

void Attachment::DeSerialize(SerializeDataView dataView)
{

}

Attachment::Attachment(String FilePath)
	: FilePath(std::move(FilePath))
{

}