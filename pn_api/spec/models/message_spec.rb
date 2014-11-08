require 'rails_helper'

RSpec.describe Message, :type => :model do
  describe 'relation with User' do
    let(:user) { FactoryGirl.create(:user) }
    let(:message) { FactoryGirl.create(:message, from_uid: user.uid) }

    it 'belongs to a user' do
      expect(message.user).to eql(user)
    end
  end

  describe 'positive negative value' do
    let(:body) { '醜いアヒルの子' }
    let(:message) { FactoryGirl.create(:message, body: body) }
    let!(:negative_word) { '醜い' }
    let!(:negative_pn_word) { create(:pn_jp_word, word: negative_word, value: -1) }

    it 'calculates positive negative value after creation' do
      expect(message.pn_value).to eq(-1)
    end
  end
end
