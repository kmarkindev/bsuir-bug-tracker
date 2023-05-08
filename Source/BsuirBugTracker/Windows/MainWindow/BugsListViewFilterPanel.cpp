#include "BugsListViewFilterPanel.h"

BugsListViewFilterPanel::BugsListViewFilterPanel(class BugsListView* BugsListViewPanel, Storage* StoragePtr)
	: BugsListView(BugsListViewPanel), StoragePtr(StoragePtr)
{

}

void BugsListViewFilterPanel::UpdateBugsList() const
{
	if(!BugsListView || !StoragePtr)
	{
		assert(false);
		return;
	}

	BugsListView->RemoveAllItems();

	for(auto& Bug : StoragePtr->GetBugs())
	{
		if((CurrentFilterData.CreatedAtRangeBegin.has_value() && Bug.GetCreatedAt() < CurrentFilterData.CreatedAtRangeBegin)
			|| (CurrentFilterData.CreatedAtRangeEnd.has_value() && Bug.GetCreatedAt() > CurrentFilterData.CreatedAtRangeEnd))
			continue;
		if((CurrentFilterData.UpdatedAtRangeBegin.has_value() && Bug.GetUpdatedAt() < CurrentFilterData.UpdatedAtRangeBegin)
		   || (CurrentFilterData.UpdatedAtRangeEnd.has_value() && Bug.GetUpdatedAt() > CurrentFilterData.UpdatedAtRangeEnd))
			continue;

		if(CurrentFilterData.BugStatus.has_value() && CurrentFilterData.BugStatus != Bug.GetBugStatus())
			continue;

		if(CurrentFilterData.BugNameSubstring.has_value()
			&& Bug.GetName().find(CurrentFilterData.BugNameSubstring->c_str()) == String::npos)
			continue;

		BugsListView->AddItem(0, &Bug);
	}
}

void BugsListViewFilterPanel::BeginLifetime()
{
	BaseWindow::BeginLifetime();


	BugNameInputText.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Название:"),
		.X = 5,
		.Y = 5,
		.Width = 280,
		.Height = 15,
		.ParentWindow = this,
	});
	BugNameSubstringTextInput.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 20,
		.Width = 280,
		.Height = 45,
		.ParentWindow = this,
	});

	BugStatusText.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Статус:"),
		.X = 5,
		.Y = 65,
		.Width = 280,
		.Height = 15,
		.ParentWindow = this,
	});
	BugStatusComboBox.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 80,
		.Width = 280,
		.Height = 15,
		.ParentWindow = this,
	});
	BugStatusComboBox.AddItem(BSUIR_TEXT("Любой"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("Ожидает исправления"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("В процессе исправления"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("В процессе тестирования"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("Исправлено"));
	BugStatusComboBox.SetSelectedIndex(0);

	CreatedAtBeginText.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Создан от:"),
		.X = 5,
		.Y = 105,
		.Width = 280,
		.Height = 15,
		.ParentWindow = this,
	});
	BugCreatedAtRangeBegin.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 120,
		.Width = 280,
		.Height = 30,
		.ParentWindow = this,
	});
	BugCreatedAtRangeBegin.ClearValue();

	CreatedAtEndText.Initialize(GetHInstance(), WindowInitializeParams {
			.Name = BSUIR_TEXT("Создан до:"),
			.X = 5,
			.Y = 150,
			.Width = 280,
			.Height = 15,
			.ParentWindow = this,
	});
	BugCreatedAtRangeEnd.Initialize(GetHInstance(), WindowInitializeParams {
			.X = 5,
			.Y = 165,
			.Width = 280,
			.Height = 30,
			.ParentWindow = this,
	});
	BugCreatedAtRangeEnd.ClearValue();

	UpdatedAtBeginText.Initialize(GetHInstance(), WindowInitializeParams {
			.Name = BSUIR_TEXT("Обновлен от:"),
			.X = 5,
			.Y = 195,
			.Width = 280,
			.Height = 15,
			.ParentWindow = this,
	});
	BugUpdatedAtRangeBegin.Initialize(GetHInstance(), WindowInitializeParams {
			.X = 5,
			.Y = 210,
			.Width = 280,
			.Height = 30,
			.ParentWindow = this,
	});
	BugUpdatedAtRangeBegin.ClearValue();

	UpdatedAtEndText.Initialize(GetHInstance(), WindowInitializeParams {
			.Name = BSUIR_TEXT("Обновлен до:"),
			.X = 5,
			.Y = 240,
			.Width = 280,
			.Height = 15,
			.ParentWindow = this,
	});
	BugUpdatedAtRangeEnd.Initialize(GetHInstance(), WindowInitializeParams {
			.X = 5,
			.Y = 255,
			.Width = 280,
			.Height = 30,
			.ParentWindow = this,
	});
	BugUpdatedAtRangeEnd.ClearValue();

	ApplyFilterButton.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Применить"),
		.X = 5,
		.Y = 478,
		.Width = 280,
		.Height = 55,
		.ParentWindow = this,
	});
	ApplyFilterButton.GetOnButtonClicked().AddCallback([this](Button&){
		RefreshBugsList();
	});

	UpdateBugsList();

	StoragePtr->GetOnBugAddOrRemove().AddCallback([this](bool WasAdd, Bug&){
		// ListView handles bug remove by itself
		if(WasAdd)
			UpdateBugsList();
	});
}

void BugsListViewFilterPanel::EndLifetime()
{
	BaseWindow::EndLifetime();

	BugNameInputText.Destroy();
	BugNameSubstringTextInput.Destroy();
	BugStatusText.Destroy();
	BugStatusComboBox.Destroy();
	CreatedAtBeginText.Destroy();
	BugCreatedAtRangeBegin.Destroy();
	CreatedAtEndText.Destroy();
	BugCreatedAtRangeEnd.Destroy();
	UpdatedAtBeginText.Destroy();
	BugUpdatedAtRangeBegin.Destroy();
	UpdatedAtEndText.Destroy();
	BugUpdatedAtRangeEnd.Destroy();
	ApplyFilterButton.Destroy();
}

void BugsListViewFilterPanel::RefreshBugsList()
{
	UpdateFilterData();

	UpdateBugsList();
}

void BugsListViewFilterPanel::UpdateFilterData()
{
	FilterData NewData {};

	const String& BugNameSubstr = BugNameSubstringTextInput.GetText();
	if(!BugNameSubstr.empty())
		NewData.BugNameSubstring = BugNameSubstr;

	int SelectedStatus = BugStatusComboBox.GetSelectedIndex() - 1;
	if(SelectedStatus >= 0 && SelectedStatus <= 3)
		NewData.BugStatus = static_cast<BugStatus>(SelectedStatus);

	if(BugCreatedAtRangeBegin.HasSelectedTime())
		NewData.CreatedAtRangeBegin = BugCreatedAtRangeBegin.GetTime();
	if(BugCreatedAtRangeEnd.HasSelectedTime())
		NewData.CreatedAtRangeEnd = BugCreatedAtRangeEnd.GetTime();

	if(BugUpdatedAtRangeBegin.HasSelectedTime())
		NewData.UpdatedAtRangeBegin = BugUpdatedAtRangeBegin.GetTime();
	if(BugUpdatedAtRangeEnd.HasSelectedTime())
		NewData.UpdatedAtRangeEnd = BugUpdatedAtRangeEnd.GetTime();

	CurrentFilterData = NewData;
}

