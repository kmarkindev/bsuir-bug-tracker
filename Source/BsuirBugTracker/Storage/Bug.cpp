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

SerializedData Bug::Serialize() const
{
	return {};
}

void Bug::DeSerialize(SerializeDataView dataView)
{

}

void Bug::AddAttachment(Attachment NewAttachment)
{

}

void Bug::RemoveAllAttachments()
{

}

void Bug::RemoveAttachment(const Attachment& Attachment)
{

}
