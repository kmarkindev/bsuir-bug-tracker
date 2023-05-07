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
			DrawViewForBug(nullptr);
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
		.Width = 435,
		.Height = 50,
		.ParentWindow = this
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
}
