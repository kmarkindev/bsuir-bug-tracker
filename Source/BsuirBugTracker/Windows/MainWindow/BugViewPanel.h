#pragma once

#include "BsuirBugTracker/Windows/Controls/Controls.h"
#include "BsuirBugTracker/Storage/Bug.h"

class BugViewPanel : public Panel
{
public:

	BugViewPanel() = default;

	BugViewPanel(const BugViewPanel&) = delete;

	BugViewPanel(BugViewPanel&& Other) noexcept = default;

	BugViewPanel& operator=(const BugViewPanel&) = delete;

	BugViewPanel& operator=(BugViewPanel&& Other) noexcept = default;

	~BugViewPanel() = default;

	void SetBug(Bug* NewBug);

	Bug* GetBug() const;

private:

	Bug* DisplayedBug {};

};
