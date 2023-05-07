#pragma once

#include <functional>
#include "BsuirBugTracker/Windows/Controls/Controls.h"
#include "BsuirBugTracker/Storage/Bug.h"
#include "BsuirBugTracker/Utils/Event.h"

class BugsListView : public ListView<Bug>
{
public:

	BugsListView() = default;

	BugsListView(const BugsListView&) = delete;

	BugsListView(BugsListView&& Other) noexcept = default;

	BugsListView& operator = (const BugsListView&) = delete;

	BugsListView& operator = (BugsListView&& Other) noexcept = default;

	int AddItem(int InsertIndex, Bug* ItemPtr) override;

	Event<int, Bug*>& GetOnBugSelectionChange();

protected:

	void BeginLifetime() override;

	// do not allow to change list view layout
	using ListView<Bug>::AddColumn;
	using ListView<Bug>::RemoveColumn;
	using ListView<Bug>::SetItemText;

	void HandleWMNotify(LPNMHDR NotifyInfo, WPARAM WParam, LPARAM LParam) override;

private:

	void FillItemWithData(int Index, Bug& Bug);

	Event<int, Bug*> OnBugSelectionChange {};

};
