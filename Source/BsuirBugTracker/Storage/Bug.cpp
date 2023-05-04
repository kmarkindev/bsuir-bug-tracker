#include "Bug.h"

const String& Bug::GetName() const
{
	return Name;
}

void Bug::SetName(const String& name)
{
	Name = name;
}

const String& Bug::GetDescription() const
{
	return Description;
}

void Bug::SetDescription(const String& description)
{
	Description = description;
}

const Timestamp& Bug::GetCreatedAt() const
{
	return CreatedAt;
}

void Bug::SetCreatedAt(const Timestamp& createdAt)
{
	CreatedAt = createdAt;
}

const Timestamp& Bug::GetUpdatedAt() const
{
	return UpdatedAt;
}

void Bug::SetUpdatedAt(const Timestamp& updatedAt)
{
	UpdatedAt = updatedAt;
}

const SerializeableList<Attachment>& Bug::GetAttachments() const
{
	return Attachments;
}

void Bug::AddAttachment(Attachment NewAttachment)
{
	Attachments.emplace_back(std::move(NewAttachment));
}

void Bug::RemoveAllAttachments()
{
	for(auto& Attachment : Attachments)
	{
		Attachment.RemoveAttachment();
	}

	Attachments.clear();
}

void Bug::RemoveAttachment(const Attachment& Attachment)
{
	auto iter = std::find(Attachments.begin(), Attachments.end(), Attachment);

	if(iter != Attachments.end())
	{
		iter->RemoveAttachment();
		Attachments.erase(iter);
	}
}

void Bug::Serialize(std::ostream& OutStream) const
{
	Guid.Serialize(OutStream);
	Name.Serialize(OutStream);
	Description.Serialize(OutStream);
	CreatedAt.Serialize(OutStream);
	UpdatedAt.Serialize(OutStream);
	Attachments.Serialize(OutStream);
}

void Bug::DeSerialize(std::istream& InStream)
{
	Guid.DeSerialize(InStream);
	Name.DeSerialize(InStream);
	Description.DeSerialize(InStream);
	CreatedAt.DeSerialize(InStream);
	UpdatedAt.DeSerialize(InStream);
	Attachments.DeSerialize(InStream);
}

bool Bug::operator==(const Bug& other) const noexcept
{
	return Guid == other.Guid;
}

const String& Bug::GetGuid() const
{
	return Guid;
}

bool Bug::IsValid() const
{
	return !Guid.empty();
}

Bug::Bug(String Guid)
	: Guid(std::move(Guid))
{

}

void Bug::RemoveBug()
{
	RemoveAllAttachments();

	Guid.clear();
}
