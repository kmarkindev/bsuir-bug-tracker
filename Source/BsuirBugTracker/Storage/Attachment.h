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

	[[nodiscard]] SerializedData Serialize() const;

	void DeSerialize(SerializeDataView dataView);

private:

	String FilePath {};

};
