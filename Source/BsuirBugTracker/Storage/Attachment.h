#pragma once

#include "BsuirBugTracker/Types/Types.h"

class Attachment
{

public:

	explicit Attachment(String FilePath);

	Attachment(const Attachment&) = delete;

	Attachment(Attachment&&) = default;

	Attachment& operator = (const Attachment&) = delete;

	Attachment& operator = (Attachment&&) noexcept = default;

	void Serialize(std::ostream& OutStream) const;

	void DeSerialize(std::istream& InStream);

private:

	String FilePath {};

};
