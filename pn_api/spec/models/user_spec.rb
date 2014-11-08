describe User do

  before(:each) { @user = FactoryGirl.create(:user) }

  subject { @user }

  it { should respond_to(:name) }

  it "#name returns a string" do
    expect(@user.name).to match 'Test User'
  end

  describe 'relation with Message' do
    let!(:message) { FactoryGirl.create(:message, to_uid: @user.uid) }
    let!(:sent_message) { FactoryGirl.create(:message, from_uid: @user.uid) }

    it 'has many messages' do
      expect(@user.messages.first).to eql(message)
    end

    it 'has many sent messages' do
      expect(@user.sent_messages.first).to eql(sent_message)
    end
  end

end
