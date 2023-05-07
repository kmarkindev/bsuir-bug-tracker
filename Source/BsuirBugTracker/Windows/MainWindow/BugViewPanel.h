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

	void UpdateBug();

protected:

	void BeginLifetime() override;

	void EndLifetime() override;

private:

	Bug* DisplayedBug {};

	size_t OnBugChangedEventHandle {};

	size_t OnBugRemovingEventHandle {};

	void BindEventsToBug(Bug* OldBug, Bug* NewBug);

	void DrawViewForBug(Bug* BugToDraw);

	Text CreatedAtText {};
	Text UpdatedAtText {};

	ComboBox BugStatusComboBox {};

	TextInput BugNameTextInput {};
	TextInput BugDescriptionTextInput {};

	Button SaveChangesButton {};

};
