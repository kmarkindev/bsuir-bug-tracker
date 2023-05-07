#include "Attachment.h"

#include <cassert>
#include "StorageHelpers.h"

Attachment::Attachment(String FilePath)
	: FilePath(std::move(FilePath))
{

}

void Attachment::Serialize(std::ostream& OutStream) const
{
	FilePath.Serialize(OutStream);
}

void Attachment::DeSerialize(std::istream& InStream)
{
	FilePath.DeSerialize(InStream);

	OnAttachmentChanged.RaiseEvent(*this);
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
		assert(false);
	}

	OnAttachmentRemoving.RaiseEvent(*this);
}

bool Attachment::IsValid() const
{
	if(FilePath.empty())
		return false;

	bool error = false;
	bool result = DoesAssetExist(FilePath, error);

	if(error)
	{
		assert(false);
	}

	return !error && result;
}

Event<Attachment&>& Attachment::GetOnAttachmentRemoving()
{
	return OnAttachmentRemoving;
}

Event<Attachment&>& Attachment::GetOnAttachmentChanged()
{
	return OnAttachmentChanged;
}
