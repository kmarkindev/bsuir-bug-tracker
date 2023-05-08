#pragma once

#include "BsuirBugTracker/Windows/Controls/Controls.h"
#include "BsuirBugTracker/Windows/Controls/Panel.h"
#include "BugsListView.h"
#include "BsuirBugTracker/Storage/Storage.h"

class BugsListViewFilterPanel : public Panel
{

	struct FilterData
	{
		std::optional<String> BugNameSubstring {};
		std::optional<BugStatus> BugStatus {};
		std::optional<Timestamp> CreatedAtRangeBegin {};
		std::optional<Timestamp> CreatedAtRangeEnd {};
		std::optional<Timestamp> UpdatedAtRangeBegin {};
		std::optional<Timestamp> UpdatedAtRangeEnd {};
	};

public:

	explicit BugsListViewFilterPanel(BugsListView* BugsListViewPanel, Storage* StoragePtr);

	BugsListViewFilterPanel(const BugsListViewFilterPanel&) = delete;

	BugsListViewFilterPanel(BugsListViewFilterPanel&& Other) noexcept = default;

	BugsListViewFilterPanel& operator=(const BugsListViewFilterPanel&) = delete;

	BugsListViewFilterPanel& operator=(BugsListViewFilterPanel&& Other) noexcept = default;

	~BugsListViewFilterPanel() = default;

	void RefreshBugsList();

protected:

	void BeginLifetime() override;

	void EndLifetime() override;

private:

	void UpdateFilterData();

	void UpdateBugsList() const;

	FilterData CurrentFilterData {};

	BugsListView* BugsListView {};

	Storage* StoragePtr {};

	Text BugNameInputText {};
	TextInput BugNameSubstringTextInput {};

	Text BugStatusText {};
	ComboBox BugStatusComboBox {};

	Text CreatedAtBeginText {};
	TimestampPicker BugCreatedAtRangeBegin {};
	Text CreatedAtEndText {};
	TimestampPicker BugCreatedAtRangeEnd {};

	Text UpdatedAtBeginText {};
	TimestampPicker BugUpdatedAtRangeBegin {};
	Text UpdatedAtEndText {};
	TimestampPicker BugUpdatedAtRangeEnd {};

	Button ApplyFilterButton {};

};
