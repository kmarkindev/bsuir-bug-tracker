#include "Attachment.h"

Attachment::Attachment(String FilePath)
	: FilePath(std::move(FilePath))
{

}

void Attachment::Serialize(std::ostream& OutStream) const
{

}

void Attachment::DeSerialize(std::istream& InStream)
{

}

bool Attachment::operator==(const Attachment& other) const noexcept
{
	return FilePath == other.FilePath;
}
