#pragma once

#include "BsuirBugTracker/Types/Types.h"
#include "BsuirBugTracker/Storage/Attachment.h"
#include "BsuirBugTracker/Types/SerializeableList.h"

class Bug
{

public:

	// Use default constructor to create nullable Bug
	// Then, you can call DeSerialize to fill it with data
	Bug() = default;

	// Use this constructor to create new Bug
	// providing not unique GUID is not safe
	explicit Bug(String Guid);

	Bug& operator = (const Bug&) = delete;

	Bug(const Bug&) = delete;

	Bug(Bug&&) = default;

	Bug& operator = (Bug&&) noexcept = default;

	[[nodiscard]] bool IsValid() const;

	[[nodiscard]] const String& GetGuid() const;

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

	// Handle removing of a bug
	// Remove all attachments etc.
	// Makes it not valid
	void RemoveBug();

private:

	String Guid {};

	String Name {};

	String Description {};

	Timestamp CreatedAt {};

	Timestamp UpdatedAt {};

	SerializeableList<Attachment> Attachments {};

};
