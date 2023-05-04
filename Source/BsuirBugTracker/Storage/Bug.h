#pragma once

#include "BsuirBugTracker/Types/Types.h"
#include <BsuirBugTracker/Storage/Attachment.h>
#include "BsuirBugTracker/Types/SerializeableList.h"

class Bug
{

public:

	Bug(String Guid, Timestamp CreatedAt, Timestamp UpdatedAt);

	[[nodiscard]] const String& GetName() const;

	void SetName(const String& name);

	[[nodiscard]] const String& GetDescription() const;

	void SetDescription(const String& description);

	[[nodiscard]] const Timestamp& GetCreatedAt() const;

	void SetCreatedAt(const Timestamp& createdAt);

	[[nodiscard]] const Timestamp& GetUpdatedAt() const;

	void SetUpdatedAt(const Timestamp& updatedAt);

	[[nodiscard]] const SerializeableList<Attachment>& GetAttachments() const;

	void AddAttachment(Attachment NewAttachment);

	void RemoveAllAttachments();

	void RemoveAttachment(const Attachment& Attachment);

	void Serialize(std::ostream& OutStream) const;

	void DeSerialize(std::istream& InStream);

	bool operator == (const Bug& other) const noexcept;

private:

	String Guid {};

	String Name {};

	String Description {};

	Timestamp CreatedAt {};

	Timestamp UpdatedAt {};

	SerializeableList<Attachment> Attachments {};

};
