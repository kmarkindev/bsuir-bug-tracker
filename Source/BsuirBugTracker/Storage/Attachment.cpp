#include "Attachment.h"

#include "StorageHelpers.h"

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

const String& Attachment::GetFilePath() const
{
	return FilePath;
}

void Attachment::RemoveAttachment()
{
	if(!IsValid())
		return;

	bool error = false;
	RemoveAsset(FilePath, error);

	FilePath.clear();

	if(error)
	{
		// TODO: log error
	}
}

bool Attachment::IsValid() const
{
	if(FilePath.empty())
		return false;

	bool error = false;
	bool result = DoesAssetExist(FilePath, error);

	if(error)
	{
		// TODO: log error
	}

	return !error && result;
}
