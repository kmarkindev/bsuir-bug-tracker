#pragma once

#include <BsuirBugTracker/Types.h>
#include <BsuirBugTracker/Storage/Attachment.h>
#include <BsuirBugTracker/Storage/SerializeableList.h>

class Bug
{

public:

	[[nodiscard]] const String& GetName() const;

	void SetName(const String& name);

	[[nodiscard]] const String& GetDescription() const;

	void SetDescription(const String& description);

	[[nodiscard]] const Timestamp& GetCreatedAt() const;

	void SetCreatedAt(const Timestamp& createdAt);

	[[nodiscard]] const Timestamp& GetUpdatedAt() const;

	void SetUpdatedAt(const Timestamp& updatedAt);

	[[nodiscard]] const SerializeableList<Attachment>& GetAttachments() const;

	void SetAttachments(const SerializeableList<Attachment>& attachments);

	[[nodiscard]] SerializedData Serialize() const;

	void DeSerialize(SerializeDataView dataView);

private:

	String Name {};

	String Description {};

	Timestamp CreatedAt {};

	Timestamp UpdatedAt {};

	SerializeableList<Attachment> Attachments {};

};
