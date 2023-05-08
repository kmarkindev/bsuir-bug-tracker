#include "BugViewPanel.h"

void BugViewPanel::SetBug(Bug* NewBug)
{
	Bug* const OldBug = DisplayedBug;
	DisplayedBug = NewBug;

	BindEventsToBug(OldBug, NewBug);

	DrawViewForBug(NewBug);
}

Bug* BugViewPanel::GetBug() const
{
	return DisplayedBug;
}

void BugViewPanel::BindEventsToBug(Bug* OldBug, Bug* NewBug)
{
	if(OldBug)
	{
		if(OnBugChangedEventHandle != 0)
		{
			OldBug->GetOnBugChanged().RemoveCallback(OnBugChangedEventHandle);
			OnBugChangedEventHandle = 0;
		}

		if(OnBugRemovingEventHandle != 0)
		{
			OldBug->GetOnBugRemoving().RemoveCallback(OnBugRemovingEventHandle);
			OnBugRemovingEventHandle = 0;
		}
	}

	if(NewBug)
	{
		OnBugChangedEventHandle = NewBug->GetOnBugChanged().AddCallback([this](Bug& Bug){
			DrawViewForBug(&Bug);
		});

		OnBugRemovingEventHandle = NewBug->GetOnBugRemoving().AddCallback([this](Bug& Bug){
			SetBug(nullptr);
		});
	}
}

void BugViewPanel::DrawViewForBug(Bug* BugToDraw)
{
	if(!BugToDraw)
	{
		SetWindowVisibility(false);
		return;
	}

	// FIXME: There is a lot of redundant allocations
	// Move labels inside BSUIR_TEXT to a separate Text control to avoid concatenations
	CreatedAtText.SetText(BSUIR_TEXT("Дата создания: ").append(TimestampToString(BugToDraw->GetCreatedAt())));
	UpdatedAtText.SetText(BSUIR_TEXT("Последнее изменение: ").append(TimestampToString(BugToDraw->GetUpdatedAt())));

	BugStatusComboBox.SetSelectedIndex(static_cast<std::int32_t>(BugToDraw->GetBugStatus()));
	BugNameTextInput.SetText(BugToDraw->GetName());
	BugDescriptionTextInput.SetText(BugToDraw->GetDescription());

	SetWindowVisibility(true);
}

void BugViewPanel::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	CreatedAtText.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 5,
		.Width = 350,
		.Height = 15,
		.ParentWindow = this
	});
	UpdatedAtText.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 25,
		.Width = 350,
		.Height = 15,
		.ParentWindow = this
	});

	BugStatusComboBox.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 45,
		.Width = 250,
		.Height = 35,
		.ParentWindow = this
	});
	BugStatusComboBox.AddItem(BSUIR_TEXT("Ожидает исправления"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("В процессе исправления"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("В процессе тестирования"));
	BugStatusComboBox.AddItem(BSUIR_TEXT("Исправлено"));

	BugNameTextInput.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 80,
		.Width = 435,
		.Height = 50,
		.ParentWindow = this
	});

	BugDescriptionTextInput.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 5,
		.Y = 135,
		.Width = 435,
		.Height = 400,
		.ParentWindow = this,
		.Styles = ES_MULTILINE
	});

	SaveChangesButton.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Сохранить"),
		.X = 5,
		.Y = 540,
		.Width = 215,
		.Height = 50,
		.ParentWindow = this
	});

	SaveChangesButton.GetOnButtonClicked().AddCallback([this](Button&) {
		UpdateBug();
	});

	RemoveBugButton.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Удалить"),
		.X = 225,
		.Y = 540,
		.Width = 215,
		.Height = 50,
		.ParentWindow = this
	});

	RemoveBugButton.GetOnButtonClicked().AddCallback([this](Button&){

		if(!DisplayedBug)
		{
			assert(false);
			return;
		}

		String Msg = BSUIR_TEXT("Подтвердите удаление бага нажав ОК");
		String Capt = BSUIR_TEXT("Подтверждение удаления");
		auto MsgResult = MessageBox(GetHwnd(), Msg.c_str(), Capt.c_str(), MB_OKCANCEL);

		if(MsgResult == IDOK)
		{
			Bug* ToRemove = DisplayedBug;

			SetBug(nullptr);

			StoragePtr->RemoveBug(*ToRemove);
		}
	});

	SetWindowVisibility(false);
}

void BugViewPanel::EndLifetime()
{
	BaseWindow::EndLifetime();

	CreatedAtText.Destroy();
	UpdatedAtText.Destroy();
	BugStatusComboBox.Destroy();
	BugNameTextInput.Destroy();
	BugDescriptionTextInput.Destroy();
	SaveChangesButton.Destroy();
	RemoveBugButton.Destroy();
}

void BugViewPanel::UpdateBug()
{
	if(!DisplayedBug)
	{
		assert(false);
		return;
	}

	int SelectedBugStatusIndex = BugStatusComboBox.GetSelectedIndex();
	if(SelectedBugStatusIndex < 0 || SelectedBugStatusIndex > 3)
		SelectedBugStatusIndex = 0;

	// We need to save values before updating
	// because each update causes view panel redraw
	// that leads to loosing entered values
	// FIXME: add more events to Bug: one for each property
	// and redraw only when updating one property
	auto NewName = BugNameTextInput.GetText();
	auto NewDescription = BugDescriptionTextInput.GetText();
	auto NewStatus = static_cast<BugStatus>(SelectedBugStatusIndex);

	DisplayedBug->SetUpdatedAt(Timestamp::GetCurrentTimestamp());
	DisplayedBug->SetName(NewName);
	DisplayedBug->SetDescription(NewDescription);
	DisplayedBug->SetBugStatus(NewStatus);
}

BugViewPanel::BugViewPanel(Storage* Storage)
	: StoragePtr(Storage)
{

}
