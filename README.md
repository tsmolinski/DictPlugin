# Dictionary Plugin

A simple plugin with a custom window where the user can create a dictionary and then save it in a json file.

## How to use

Locate the Dict tab in the Window and click on it.

![DictTab](https://github.com/user-attachments/assets/3968380d-5a38-4721-83ee-b436aa8ca3e6)

Click the Add element button to add an entry to the dictionary.

![DictWindow](https://github.com/user-attachments/assets/f2abecd5-17b9-4af0-a723-9610cc75a925)

## Usage

The plugin contains two classes derived from SCompoundWidget - the main widget SDictionaryWidget and the input widget SDictionaryEntryWidget.

SDictionaryEntryWidget uses .OnTextCommitted to inform SDictionaryWidget of changes to a key or value. Also .OnClicked for the Remove function, which tells the main widget which key-value pair to remove from the dictionary.

SDictionaryWidget has a dictionary entry and buttons Add item, Save to Json. It also handles key/value changes in the dictionary (which is a simple TMap<FString, FString>) using the SDictionaryWidget::UpdateDictionaryEntry(FString Key, FString Value, FString OldKey) method (we use OldKey to know if the user changes the key or value) to manipulate our dictionary.
