# Feature: Compose new message
#   As a user
#   I want to compose new message
#   So I can tell someone my real feelings
feature 'Compose new message', :omniauth do
  scenario 'user can compose new message' do
    signin
    visit 'messages/new'
    # Example user is selected
    fill_in 'Body', with: 'Hello'
    click_button 'Send'
    new_message = Message.last
    expect(new_message.body).to eql('Hello')
  end
end
