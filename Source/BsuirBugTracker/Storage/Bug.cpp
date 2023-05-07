#include "Bug.h"

const String& Bug::GetName() const
{
	return Name;
}

void Bug::SetName(const String& name)
{
	Name = name;

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
}

const String& Bug::GetDescription() const
{
	return Description;
}

void Bug::SetDescription(const String& description)
{
	Description = description;

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
}

const Timestamp& Bug::GetCreatedAt() const
{
	return CreatedAt;
}

void Bug::SetCreatedAt(const Timestamp& createdAt)
{
	CreatedAt = createdAt;

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
}

const Timestamp& Bug::GetUpdatedAt() const
{
	return UpdatedAt;
}

void Bug::SetUpdatedAt(const Timestamp& updatedAt)
{
	UpdatedAt = updatedAt;

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
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

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
}

void Bug::RemoveAttachment(const Attachment& Attachment)
{
	auto iter = std::find(Attachments.begin(), Attachments.end(), Attachment);

	if(iter != Attachments.end())
	{
		iter->RemoveAttachment();
		Attachments.erase(iter);
	}

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
}

void Bug::Serialize(std::ostream& OutStream) const
{
	Guid.Serialize(OutStream);
	Name.Serialize(OutStream);
	SerializeInteger(OutStream, static_cast<std::int32_t>(BugStatus));
	Description.Serialize(OutStream);
	CreatedAt.Serialize(OutStream);
	UpdatedAt.Serialize(OutStream);
	Attachments.Serialize(OutStream);
}

void Bug::DeSerialize(std::istream& InStream)
{
	Guid.DeSerialize(InStream);
	Name.DeSerialize(InStream);
	BugStatus = static_cast<enum BugStatus>(DeSerializeInteger(InStream));
	Description.DeSerialize(InStream);
	CreatedAt.DeSerialize(InStream);
	UpdatedAt.DeSerialize(InStream);
	Attachments.DeSerialize(InStream);

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
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
	auto Now = Timestamp { std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()) };

	CreatedAt = Now;
	UpdatedAt = Now;
}

void Bug::RemoveBug()
{
	OnBugRemoving.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(false, *this);

	RemoveAllAttachments();

	Guid.clear();
}

Event<Bug&>& Bug::GetOnBugChanged()
{
	return OnBugChanged;
}

Event<Bug&>& Bug::GetOnBugRemoving()
{
	return OnBugRemoving;
}

BugStatus Bug::GetBugStatus() const
{
	return BugStatus;
}

void Bug::SetBugStatus(enum BugStatus InBugStatus)
{
	BugStatus = InBugStatus;

	OnBugChanged.RaiseEvent(*this);
	OnAnyBugChangedOrRemoved.RaiseEvent(true, *this);
}

String Bug::GetBugStatusString(enum BugStatus StatusToConvert)
{
	switch (StatusToConvert)
	{
	case BugStatus::Todo:
		return BSUIR_TEXT("Ожидает исправления");
	case BugStatus::InProgress:
		return BSUIR_TEXT("В процессе исправления");
	case BugStatus::InQa:
		return BSUIR_TEXT("В процессе тестирования");
	case BugStatus::Done:
		return BSUIR_TEXT("Исправлено");
	}

	assert(false);
	return {};
}
