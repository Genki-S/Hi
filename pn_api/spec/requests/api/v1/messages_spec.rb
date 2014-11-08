require 'spec_helper'

describe 'Messages API v1', type: :request do
  describe 'GET /messages/:id' do
    let(:body) { 'Hello' }
    let(:message) { create(:message, body: body) }

    it 'returns message' do
      get "/api/v1/messages/#{message.id}", format: 'json'
      expect(response).to be_success
      json = JSON.parse(response.body)
      expect(json['body']).to eq(body)
    end

    it 'opens message' do
      get "/api/v1/messages/#{message.id}", format: 'json'
      expect(response).to be_success
      json = JSON.parse(response.body)
      expect(json['opened_at']).to_not be_nil
    end
  end

  describe 'POST /messages' do
    let(:sender) { create(:user) }
    let(:recipient) { create(:user) }
    let(:body) { 'Hello' }

    let(:message_params) do
      {
        from_uid: sender.uid,
        to_uid: recipient.uid,
        body: body
      }
    end

    it 'creates new message' do
      post '/api/v1/messages', message: message_params, format: 'json'
      created_message = Message.last
      expect(created_message.from_uid).to eq(sender.uid)
      expect(created_message.to_uid).to eq(recipient.uid)
      expect(created_message.body).to eq(body)
    end
  end
end
