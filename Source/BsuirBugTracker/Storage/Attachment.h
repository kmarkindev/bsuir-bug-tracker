#pragma once

#include "BsuirBugTracker/Types/Types.h"

class Attachment
{

public:

	// Use it to create nullable Attachment
	// You can fill it with data using DeSerialize
	Attachment() = default;

	// Use this constructor to create new Attachment
	// providing not unique file path is not safe
	explicit Attachment(String FilePath);

	Attachment(const Attachment&) = delete;

	Attachment(Attachment&&) = default;

	Attachment& operator = (const Attachment&) = delete;

	Attachment& operator = (Attachment&&) noexcept = default;

	void Serialize(std::ostream& OutStream) const;

	void DeSerialize(std::istream& InStream);

	bool operator == (const Attachment& other) const noexcept;

	[[nodiscard]] const String& GetFilePath() const;

	// Use it to remove physical file
	// This call makes Attachment not valid
	void RemoveAttachment();

	[[nodiscard]] bool IsValid() const;

private:

	// Attachment file path relative to storage folder
	String FilePath {};

};
